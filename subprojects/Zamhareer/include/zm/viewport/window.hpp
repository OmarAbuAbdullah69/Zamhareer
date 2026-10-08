#pragma once

#include "GLFW/glfw3.h"
#include <string>
namespace zm {
class viewport;
class window {
  friend class viewport;

private:
  window(const char *title, int width, int height);
  ~window();
  void update();
  bool shouldClose() const { return glfwWindowShouldClose(mHandle); }
  inline std::string getTitle() const { return mTitle; }
  void getSize(int &w, int &h) const {
  glfwGetWindowSize(mHandle, &w, &h);
  }
  void setTitle(const char *title);
  void setSize(int width, int height);
	void setWindowResizeable(bool r) {glfwSetWindowAttrib(mHandle, GLFW_RESIZABLE, r);}

private:
  std::string mTitle;
  GLFWwindow *mHandle;
};
} // namespace zm
