#pragma once

#ifndef WINDOWING
#error "WINDOWING must be defined to 0 or 1 (link against zmlib_dep)"
#endif
#if WINDOWING
#include "window.hpp"
#endif
namespace zm {
class engine;


struct viewportSettings {
  std::string title;
  int width = 640;
  int height = 480;
	bool resizable = true;
};

class viewport {
  friend class engine;

private:
  viewport(viewportSettings);
  ~viewport();
  void update();
  bool shouldClose() const;

private:
#if WINDOWING
  window *mWindow;
#endif
};
} // namespace zm
