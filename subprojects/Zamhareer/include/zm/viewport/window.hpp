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
  int getWidth() const { return mWidth; }
  int getHeight() const { return mHeight; }
  void setTitle(const char *title);
  void setWidth(int width);
  void setheight(int height);

private:
  std::string mTitle;
  int mWidth, mHeight;
  GLFWwindow *mHandle;
};
} // namespace zm
