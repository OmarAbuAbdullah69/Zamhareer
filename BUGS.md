# Bug log

Debug pass on commit `8b7c98b` ("at this point U should see a blank window").
Built with meson 1.10.1, g++ 15.2, GLFW 3.4, on Ubuntu (Wayland session).

Each entry says whether it was **reproduced** (actually ran and observed) or
**read** (found by reading the code, not triggered).

| # | Severity | Bug | Status |
|---|----------|-----|--------|
| 1 | High | Window shows garbage / looks glitchy | reproduced |
| 2 | High | Closing the window doesn't stop the app | reproduced |
| 3 | High | Release build doesn't configure (`elif` with no condition) | reproduced |
| 4 | Medium | `-o3` instead of `-O3` in release flags | read |
| 5 | Medium | Deleting an engine that never ran `init()` segfaults | reproduced |
| 6 | Medium | `engine::instance()` fails to link | reproduced |
| 7 | Medium | Any GLFW error kills the app with `exit(1)` | read |
| 8 | Medium | `glfwInit()` failure is logged but ignored | read |
| 9 | Medium | `#ifdef WINDOWING` is always true | read |
| 10 | Low | Log output is lost when stdout is not a terminal | reproduced |
| 11 | Low | `engine` destructor is not virtual | read |
| 12 | Low | `{%9}` placeholder reads past the end of `argBuffer` | read |
| 13 | Low | `matchKey` can read past the end of the string | read |

---

### 1. Window shows garbage / looks glitchy
**Where:** `src/zm.cpp` `engine::render()` and `src/viewport/window.cpp` `window::update()`

The loop calls `glfwSwapBuffers` every frame, but nothing ever draws to or
clears the back buffer, so the GPU shows whatever leftover memory is in it.
That is why the window flickers with junk instead of being blank.

**Evidence:** reading the never-cleared back buffer of a 200x200 window gave
**265 distinct colours**. After one `glClear` it was **1**.

**Fix:** clear every frame before swapping, e.g. in `window::update()`:
```cpp
glClearColor(0.f, 0.f, 0.f, 1.f);
glClear(GL_COLOR_BUFFER_BIT);
glfwSwapBuffers(mHandle);
glfwPollEvents();
```
(Needs `-lGL` / `dependency('gl')` in meson.) Also consider setting
`glfwSwapInterval(1)` after `glfwMakeContextCurrent` so the frame rate is
capped explicitly. The app also asks for a 20x20 window (`app.hpp`), which
some compositors resize without the engine noticing, because there is no
framebuffer-size callback.

### 2. Closing the window doesn't stop the app
**Where:** `src/zm.cpp`. Nothing checks `glfwWindowShouldClose`.

`mRuning` is set to `true` in `app()` and never becomes `false`, so clicking X
does nothing and the `while (a.isRuning())` loop in `ZM_MAIN` runs forever.

**Evidence:** called `glfwSetWindowShouldClose(window, true)` and ran the loop:
it was still running after 200 frames.

**Fix:** after polling events, e.g. in `engine::render()` (or have
`viewport`/`window` expose a `shouldClose()`):
```cpp
if (glfwWindowShouldClose(handle)) mRuning = false;
```

### 3. Release build doesn't configure
**Where:** `subprojects/Zamhareer/meson.build:17`
```meson
elif
  add_project_arguments('-DREL_BUILD', '-o3', language: 'cpp')
```
`elif` has no condition. In debug mode meson never reaches it, which is why
the bug stayed hidden.

**Evidence:** `meson setup build-rel -DZamhareer:build_mode=release` gives
`meson.build:17:4: ERROR: Unknown statement.`

**Fix:** `elif` → `else`.

### 4. `-o3` instead of `-O3`
**Where:** same line as #3. Lowercase `-o3` means "write the output to a file
named `3`", not "optimise". It should be `-O3`. Better still, drop the manual
`-g`/`-O3` flags and use meson's built-in `buildtype` (meson already warns
about `-g`).

### 5. Deleting an engine that never ran `init()` segfaults
**Where:** `include/zm/zm.hpp`, `viewport *mViewport;` (never initialised)

`~engine()` checks `if (mViewport)`, but the pointer holds garbage unless
`init()` ran, so it deletes a random address.

**Evidence:** constructing and destroying an engine without `init()` →
`Segmentation fault`, exit 139.

**Fix:** `viewport *mViewport = nullptr;`

### 6. `engine::instance()` fails to link
**Where:** `include/zm/zm.hpp`. `static engine *sInstance;` is declared but
never defined, and nothing assigns it.

**Evidence:** calling `zm::engine::instance()` →
`undefined reference to 'zm::engine::sInstance'`.

**Fix:** define it in `zm.cpp` (`engine *engine::sInstance = nullptr;`), set
`sInstance = this;` in the constructor, or delete it until it's needed.

### 7. Any GLFW error kills the app
**Where:** `src/viewport/window.cpp:7-10`. The error callback calls `exit(1)`.

GLFW reports many non-fatal errors this way (for example, Wayland refuses to
let windows set their own position), and each one would end the program
without running destructors. The old commit message about window pos/size
problems may be this.

**Fix:** log in the callback and don't exit. Treat errors as fatal only where a
call actually fails (e.g. the `!mHandle` check already there). Also set the
callback **before** `glfwInit()` (it's currently set after), so init errors are
reported too.

### 8. `glfwInit()` failure is ignored
**Where:** `src/viewport/viewport.cpp:7-9`. On failure it logs and then goes
on to create a window anyway. It should stop there (return or exit).

### 9. `#ifdef WINDOWING` is always true
**Where:** `viewport.hpp`, `viewport.cpp`

meson defines `WINDOWING=1` or `WINDOWING=0`, and `#ifdef` only checks whether
the macro exists, so the Android build (`WINDOWING=0`) still compiles the GLFW
code. Use `#if WINDOWING`. `viewport::update()` also uses `mWindow` outside
the guard, so it will break once the guard works.

### 10. Log output is lost when not on a terminal
**Where:** `include/zm/external/zmprinter.hpp`, `printer::render()`

It writes to `std::cout` without flushing. On a terminal you see lines,
but piped or redirected (IDE console, `./app > log.txt`) they stay in the
buffer and are lost if the app is killed. Since the app can't be closed
normally (#2), that's always the case.

**Evidence:** `timeout 3 ./build/app` printed nothing. The same command under a
pseudo-terminal printed the `INFO` line.

**Fix:** `std::cout << output.str() << std::flush;` (or use `std::cerr` for
errors).

### 11. `engine` destructor is not virtual
**Where:** `include/zm/zm.hpp`, `~engine();`

`engine` has virtual methods and is meant to be subclassed. Deleting an `app`
through an `engine*` would skip `~app()`. Make it `virtual ~engine();`.

### 12. `{%9}` reads out of bounds
**Where:** `zmprinter.hpp`, `parsePlaceholders`. `argBuffer` has 9 slots
(0–8), but any digit is accepted, so `{%9}` reads `argBuffer[9]`. Check
`key - '0' < argBuffer.size()`.

### 13. `matchKey` can read past the end of the string
**Where:** `zmprinter.hpp`, `matchKey`. It reads `str[i + 3]` before checking
that `str[i + 2]` isn't the terminator, so a message ending in `{%` reads one
byte past the end. Check `str[i + 2] != '\0'` first.

---

### Housekeeping (not bugs)
- No `.gitignore`. `build/` and `.cache/clangd/` show up in `git status`, and
  clangd index files were committed earlier. Suggest ignoring `build*/` and
  `.cache/`.
- `meson.build` finds sources with `run_command('find', ...)`, so new files
  aren't picked up until meson reconfigures. List them explicitly instead.
