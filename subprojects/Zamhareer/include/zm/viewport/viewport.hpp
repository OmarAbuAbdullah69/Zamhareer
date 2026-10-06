#pragma once

#ifndef WINDOWING
#error "WINDOWING must be defined to 0 or 1 (link against zmlib_dep)"
#endif
#if WINDOWING
#include "window.hpp"
#endif
namespace zm {
class engine;
class viewport {
  friend class engine;

private:
  viewport(const char *title, int width, int height);
  ~viewport();
  void update();
  bool shouldClose() const;

private:
#if WINDOWING
  window *mWindow;
#endif
};
} // namespace zm
