// Self-checks for the parts of the engine that run without a display.
// Run with: meson test -C build
#include "zm/zm.hpp"
#include "zm/external/zmprinter.hpp"
#include <cstring>
#include <iostream>
#include <new>
#include <sstream>
#include <type_traits>

static_assert(std::has_virtual_destructor<zm::engine>::value, "engine is subclassed, so its destructor must be virtual");
static_assert(!std::is_copy_constructible<zm::engine>::value, "copying an engine would delete its viewport twice");

static int failures = 0;
#define CHECK(cond)                                                            \
  do {                                                                         \
    if (!(cond)) {                                                             \
      std::cerr << "FAIL line " << __LINE__ << ": " #cond "\n";                \
      ++failures;                                                              \
    }                                                                          \
  } while (0)

template <typename... Args>
static std::string printed(zm::printer &p, const char *msg, const Args &...args) {
  std::stringstream out;
  auto *old = std::cout.rdbuf(out.rdbuf());
  p.print(msg, args...);
  std::cout.rdbuf(old);
  return out.str();
}

struct testEngine : zm::engine {};

int main() {
  zm::printer p("{%m}");

  // placeholders 0-9 are all usable
  CHECK(printed(p, "{%9}", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9) == "9");

  // args from an earlier call must not leak into a later one
  printed(p, "{%0}{%1}", "a", "b");
  CHECK(printed(p, "{%0}{%1}", "c") == "c");

  // a message ending in "{%" must not read past its terminator
  char *tail = new char[4];
  std::memcpy(tail, "x{%", 4);
  CHECK(printed(p, tail) == "x{%");
  delete[] tail;

  // destroying an engine that never ran init() must not touch its viewport
  alignas(testEngine) unsigned char buf[sizeof(testEngine)];
  std::memset(buf, 0xAB, sizeof buf);
  testEngine *e = new (buf) testEngine;
  CHECK(&zm::engine::inst() == e);
  e->~testEngine();

  if (failures == 0)
    std::cout << "all checks passed\n";
  return failures == 0 ? 0 : 1;
}
