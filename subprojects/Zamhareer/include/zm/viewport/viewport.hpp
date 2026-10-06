#pragma once

#include "window.hpp"
namespace zm {
class engine;
class viewport {
  friend class engine;

private:
#ifdef WINDOWING
  viewport(const char *title, int width, int height);
#endif
  ~viewport();
  void update();
  bool shouldClose() const;

private:
#ifdef WINDOWING
  window *mWindow;
#endif
};
} // namespace zm
