#include "zm/viewport/window.hpp"
#include "zm/events.hpp"
#include "zm/input.hpp"
#include "zm/zm.hpp"
#include <GLFW/glfw3.h>
#if WINDOWING
#include "zm/logger.hpp"
#include <cstdlib>
namespace zm {
window::window(const char *title, int width, int height) : mTitle(title) {
  mHandle = glfwCreateWindow(width, height, mTitle.c_str(), nullptr, nullptr);
  if (!mHandle) {
    LOGERROR("couldn't make a Glfw window with name = {%0}, width = {%1}, "
             "height = {%2}",
             mTitle, width, height);
    std::exit(1);
  }
  LOGINFO(
      "a Glfw window was made with name = {%0}, width = {%1}, height = {%2}",
      mTitle, width, height);
  glfwMakeContextCurrent(mHandle);
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSetWindowSizeCallback(mHandle, [](GLFWwindow *window, int w, int h) {
    engine::inst().onEvent(event{.type = eventType::WindowResized,
                                     .windowResize{.width = w, .height = h}});
  });
  glfwSetWindowCloseCallback(mHandle, [](GLFWwindow *) {
    engine::inst().onEvent(event{.type = eventType::WindowClosed});
  });
  glfwSetWindowFocusCallback(mHandle, [](GLFWwindow *, int f) {
    engine::inst().onEvent(event{.type = (f == GLFW_TRUE)
                                                 ? eventType::WindowFocused
                                                 : eventType::WindowUnfocused});
  });

  glfwSetKeyCallback(mHandle, [](GLFWwindow *window, int code, int scancode,
                                 int action, int mods) {
		event e;
    mod m = mod::None;
    if (mods & GLFW_MOD_SHIFT)
      m = m | mod::Shift;
    if (mods & GLFW_MOD_CONTROL)
      m = m | mod::Ctrl;
    if (mods & GLFW_MOD_ALT)
      m = m | mod::Alt;
    if (mods & GLFW_MOD_SUPER)
      m = m | mod::Super;
    if (mods & GLFW_MOD_CAPS_LOCK)
      m = m | mod::CapsLock;
    if (mods & GLFW_MOD_NUM_LOCK)
      m = m | mod::NumLock;
    switch (action) {
    case GLFW_PRESS:
          e = event{.type = eventType::KeyPressed,
                .key{.code = KEY_GLFW_2_ZM(code), .modifiers = m}};
      break;
    case GLFW_REPEAT:
         e =  event{.type = eventType::keyRepeat,
                .key{.code = KEY_GLFW_2_ZM(code), .modifiers = m}};
      break;
    case GLFW_RELEASE:
          e = event{.type = eventType::KeyReleased,
                .key{.code = KEY_GLFW_2_ZM(code), .modifiers = m}};
      break;
    }
		engine::inst().onEvent(e);
		input::inst().listen(e);
  });

  glfwSetCharCallback(mHandle, [](GLFWwindow *window, unsigned int codepoint) {
    engine::inst().onEvent(
        event{.type = eventType::TextInput, .text{.codepoint = codepoint}});
  });

  glfwSetCursorPosCallback(
      mHandle, [](GLFWwindow *window, double xpos, double ypos) {
            event e = event{.type = eventType::MouseMoved,
                  .mouseMove{.x = (float)xpos, .y = (float)ypos}};
        engine::inst().onEvent(e);
				input::inst().listen(e);
      });

  glfwSetMouseButtonCallback(
      mHandle, [](GLFWwindow *window, int button, int action, int mods) {
			event e;
        mod m = mod::None;
        if (mods & GLFW_MOD_SHIFT)
          m = m | mod::Shift;
        if (mods & GLFW_MOD_CONTROL)
          m = m | mod::Ctrl;
        if (mods & GLFW_MOD_ALT)
          m = m | mod::Alt;
        if (mods & GLFW_MOD_SUPER)
          m = m | mod::Super;
        if (mods & GLFW_MOD_CAPS_LOCK)
          m = m | mod::CapsLock;
        if (mods & GLFW_MOD_NUM_LOCK)
          m = m | mod::NumLock;
        switch (action) {
        case GLFW_PRESS:
             e =  event{.type = eventType::MouseButtonPressed,
                    .mouseButton{.button = MOUSEBUTTIN_GLFW_2_ZM(button),
                                 .modifiers = m}};
          break;
        case GLFW_RELEASE:
              e = event{.type = eventType::MouseButtonReleased,
                    .mouseButton{.button = MOUSEBUTTIN_GLFW_2_ZM(button),
                                 .modifiers = m}};
          break;
        }
				engine::inst().onEvent(e);
				input::inst().listen(e);
      });

  glfwSetScrollCallback(
      mHandle, [](GLFWwindow *window, double xoffset, double yoffset) {
        engine::inst().onEvent(
            event{.type = eventType::MouseScrolled,
                  .mouseScroll{.x = (float)xoffset, .y = (float)yoffset}});
      });

  engine::inst().onEvent(
      event{.type = eventType::WindowCreated,
            .windowResize{.width = width, .height = height}});
}
window::~window() { glfwDestroyWindow(mHandle); }
void window::update() {
  glfwSwapBuffers(mHandle);
  glfwPollEvents();
  // back buffer is undefined after a swap; clear it so the next frame starts
  // clean
  glClear(GL_COLOR_BUFFER_BIT);
}
void window::setTitle(const char *title) {
  mTitle = title;
  glfwSetWindowTitle(mHandle, title);
}
void window::setSize(int width, int height) {
  glfwSetWindowSize(mHandle, width, height);
}
} // namespace zm
#endif
