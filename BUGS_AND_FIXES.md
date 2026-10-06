# Bugs and fixes

Debug passes starting from commit `8b7c98b` ("at this point U should see a
blank window"). Built with meson 1.10.1, g++ 15.2, GLFW 3.4, on Ubuntu (Wayland
session).

**All 23 bugs below are fixed.** "How found" says whether a bug was
**reproduced** (ran it and saw it fail) or **read** (found by reading the code).

## How it was verified

- Clean builds of all three configs: debug, release
  (`-DZamhareer:build_mode=release`) and android (`-DZamhareer:platform=android`,
  no GLFW). All build with **0 warnings**.
- `meson test -C build` runs `subprojects/Zamhareer/tests/test_zm.cpp`, which
  checks the printer, engine cleanup and `instance()`. It passes in every config
  and also passes under AddressSanitizer, UBSan and libstdc++ bounds checks.
- Display checks: the frame shown is 1 clean colour (was 265 junk colours),
  the loop stops 1 frame after a close request, and clicking X closes the app
  (checked by hand).

## Summary

| # | Severity | Bug | How found |
|---|----------|-----|-----------|
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
| 11 | Low | `engine` destructor is not virtual | reproduced (static_assert) |
| 12 | Low | `{%9}` placeholder reads past the end of `argBuffer` | reproduced |
| 13 | Low | `matchKey` can read past the end of the string | read |
| 14 | High | App code and engine code disagree on `WINDOWING` | read |
| 15 | Medium | GLFW/GL headers not passed on to code that uses the engine | read |
| 16 | Medium | `engine` can be copied, so its viewport gets deleted twice | reproduced (static_assert) |
| 17 | Medium | `glfwTerminate()` called by `window` instead of `viewport`, which calls `glfwInit()` | read |
| 18 | Low | `window` setters don't change the real window | read |
| 19 | Low | Printer reuses arguments left over from the previous log call | read |
| 20 | Medium | C++17 is required but never requested | read |
| 21 | Low | Build options accept any string, so typos silently misconfigure | read |
| 22 | Low | `-Wsign-compare` warnings in the printer | reproduced |
| 23 | Low | `app.hpp` includes GLFW without using it | read |

---

## Details

### 1. Window shows garbage / looks glitchy
The loop swapped buffers every frame but never drew to or cleared the back
buffer, so the GPU showed leftover memory. A 200x200 window's frame had **265
distinct colours**.

**Fix:** `window` clears once when the GL context is made and again right
after every `glfwSwapBuffers`. Clearing after the swap rather than before means
anything `app::render()` draws before calling `engine::render()` isn't wiped.
Added `dependency('gl')` for `glClear`.

### 2. Closing the window doesn't stop the app
Nothing checked `glfwWindowShouldClose`, so `mRuning` never became `false`. The
loop was still running 200 frames after a close request.

**Fix:** `window::shouldClose()` → `viewport::shouldClose()`. After polling
events, `engine::render()` sets `mRuning = false`.

### 3. Release build doesn't configure
`meson.build:17` had `elif` with no condition:
`meson.build:17:4: ERROR: Unknown statement.` It was hidden because debug mode
never reaches that line.

**Fix:** `elif` → `else`.

### 4. `-o3` instead of `-O3`
Lowercase `-o3` means "write the output to a file named `3`".

**Fix:** `-O3`. Confirmed in `build-rel/compile_commands.json`.

### 5. Deleting an engine that never ran `init()` segfaults
`viewport *mViewport;` was never initialised, so `~engine()` deleted a garbage
address (segfault, exit 139).

**Fix:** `viewport *mViewport = nullptr;`. Covered by the test.

### 6. `engine::instance()` fails to link
`sInstance` was declared but never defined or assigned:
`undefined reference to 'zm::engine::sInstance'`.

**Fix:** defined in `zm.cpp`. The constructor sets it to `this`, and the
destructor clears it. Covered by the test.

### 7. Any GLFW error kills the app
The error callback called `exit(1)`, so even non-fatal GLFW errors (e.g.
Wayland refusing to move a window) ended the program. It was also installed
after `glfwInit()`, so init errors weren't reported.

**Fix:** the callback only logs, and it now lives in `viewport` and is
installed before `glfwInit()`. Real failures (`glfwInit`, window creation)
still exit.

### 8. `glfwInit()` failure is ignored
It logged and then went on to create a window anyway.

**Fix:** it now logs and exits.

### 9. `#ifdef WINDOWING` is always true
meson defines `WINDOWING` as `0` or `1`, so `#ifdef` was always true.

**Fix:** `#if WINDOWING` everywhere. `viewport`'s constructor, `update()` and
`shouldClose()` now exist in both modes, with stubs when there's no windowing,
and all of `window.cpp` is inside `#if WINDOWING`. A missing `WINDOWING` is a
compile error (`#error`) instead of silently meaning 0. The android config now
builds without GLFW.

### 10. Log output is lost when not on a terminal
`printer::render()` didn't flush `std::cout`, so piped or redirected output
was lost when the app was killed.

**Fix:** `<< std::flush`. `./build/app > log.txt` now contains the `INFO` line.

### 11. `engine` destructor is not virtual
**Fix:** `virtual ~engine();`. Checked by a `static_assert` in the test.

### 12. `{%9}` reads out of bounds
`argBuffer` had 9 slots but all 10 digits were accepted. The libstdc++ bounds
check aborted on `{%9}`.

**Fix:** `argBuffer` has 10 slots, one per digit. `isdigit` gets an
`unsigned char`. Covered by the test.

### 13. `matchKey` can read past the end of the string
For a message ending in `{%`, it read `str[i + 3]`, one byte past the
terminator.

**Fix:** check `str[i + 2] != '\0'` first. Covered by the test, which passes
under AddressSanitizer.

### 14. App code and engine code disagree on `WINDOWING`
`-DWINDOWING` was only added while compiling the engine library. `app.hpp`
includes the same headers without it, so the app saw a different `viewport`
class than the library (a One Definition Rule violation, which is undefined
behaviour).

**Fix:** `zmlib_dep` passes the same `WINDOWING` value to everything that
uses it.

### 15. GLFW/GL headers not passed on
`zmlib_dep` didn't carry the GLFW/GL dependencies, so code using the engine
only compiled when GLFW happened to be installed system-wide (not the case on
Windows, for example).

**Fix:** `dependencies: deps` in `zmlib_dep`.

### 16. `engine` can be copied
The compiler-generated copy shares the raw `mViewport` pointer, so both copies
would delete it.

**Fix:** copy constructor and copy assignment are deleted. Checked by a
`static_assert`.

### 17. `glfwTerminate()` in the wrong place
`viewport` calls `glfwInit()`, but `~window()` called `glfwTerminate()`. That
would end GLFW for every window as soon as any one window was destroyed.

**Fix:** `~viewport()` terminates GLFW after deleting its window.

### 18. `window` setters don't change the real window
`setTitle`/`setWidth`/`setheight` only updated the member variables.

**Fix:** they call `glfwSetWindowTitle` / `glfwSetWindowSize`. `setheight` was
renamed to `setHeight` to match the others.

### 19. Printer reuses old arguments
`argBuffer` wasn't cleared between calls, so `{%1}` in a call with one argument
printed the previous call's second argument.

**Fix:** the buffer is cleared after each print. Covered by the test.

### 20. C++17 never requested
The printer uses `std::string_view`, but neither `project()` set `cpp_std`.
Compilers that default to C++14 (MSVC, older clang) would fail.

**Fix:** `default_options: ['cpp_std=c++17']` in both `project()` calls, plus
an explicit `#include <string_view>`.

### 21. Build options accept any string
`build_mode=Release` (capital R) silently fell through to release flags, and
an unknown platform left out every `PLAT_*` define.

**Fix:** the options are `combo` types with fixed choices, and meson rejects
typos.

### 22. `-Wsign-compare` warnings
`int argIndex` was compared against `argBuffer.size()`.

**Fix:** `std::size_t argIndex`.

### 23. Unused GLFW include in `app.hpp`
**Fix:** removed. The app only needs `zm/zm.hpp`.

---

### Housekeeping
- Added `.gitignore` for `build*/` and `.cache/`.
- Still open, not bugs:
  - `meson.build` finds sources with `run_command('find', ...)`, so new files
    need a reconfigure.
  - meson warns that `-g` should be the built-in `debug` option.
  - The app asks for a 20x20 window.
