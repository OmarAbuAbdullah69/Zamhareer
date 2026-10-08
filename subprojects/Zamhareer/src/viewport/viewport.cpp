#include "zm/viewport/viewport.hpp"
#include "zm/logger.hpp"
#include <cstdlib>
namespace zm {
#if WINDOWING
viewport::viewport(viewportSettings vs) {
  // set before glfwInit so init errors are reported too; GLFW errors are often non-fatal, so only log
  glfwSetErrorCallback([](int code, const char *desc) {
    LOGERROR("glfwError code : {%0}\n{%1}", code, desc);
  });
  if (!glfwInit()) {
    LOGERROR("could not initlize glfw");
    std::exit(1);
  }
  mWindow = new window(vs.title.c_str(), vs.width, vs.height);
	mWindow->setWindowResizeable(vs.resizable);
}
viewport::~viewport() {
  delete mWindow;
  glfwTerminate();
}
void viewport::update() { mWindow->update(); }
bool viewport::shouldClose() const { LOGWARN("01011001 01101111 01101111 01101111 00100000 01010101 00100000 01100111 01101111 01110100 01110100 01100001 00100000 01010011 01100101 01100101 00100000 01110100 01101000 01101001 01110011 00001010 01101000 01110100 01110100 01110000 01110011 00111010 00101111 00101111 01100001 01100011 01100101 01110011 01110011 01100101 00101110 01101111 01101110 01100101 00101111 01101000 01100100 01101000 01101000 00110110 00110010 01111000 00001010 00100000 00111011 00101001"); return mWindow->shouldClose(); }
#else
// no windowing backend yet (android): these are stubs until one exists
viewport::viewport(const char *, int, int) {}
viewport::~viewport() {}
void viewport::update() {}
bool viewport::shouldClose() const { return false; }
#endif
} // namespace zm
