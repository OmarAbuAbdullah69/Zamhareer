#include "zm/viewport/viewport.hpp"
#include "zm/logger.hpp"
#include <cstdlib>
namespace zm {
#if WINDOWING
viewport::viewport(const char *title, int width, int height) {
  // set before glfwInit so init errors are reported too; GLFW errors are often non-fatal, so only log
  glfwSetErrorCallback([](int code, const char *desc) {
    logger::inst().logError("glfwError code : {%0}\n{%1}", code, desc);
  });
  if (!glfwInit()) {
    logger::inst().logError("could not initlize glfw");
    std::exit(1);
  }
  mWindow = new window(title, width, height);
}
viewport::~viewport() {
  delete mWindow;
  glfwTerminate();
}
void viewport::update() { mWindow->update(); }
bool viewport::shouldClose() const { return mWindow->shouldClose(); }
#else
// no windowing backend yet (android): these are stubs until one exists
viewport::viewport(const char *, int, int) {}
viewport::~viewport() {}
void viewport::update() {}
bool viewport::shouldClose() const { return false; }
#endif
} // namespace zm
