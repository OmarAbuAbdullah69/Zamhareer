#include "zm/viewport/viewport.hpp"
#include "zm/logger.hpp"
#include <GLFW/glfw3.h>
namespace zm {
#ifdef WINDOWING
	viewport::viewport(const char *title, int width, int height) {
		if(!glfwInit()) logger::inst().logError("could not initlize glfw");
		mWindow = new window(title , width, height);
	}
#endif
	viewport::~viewport() {
#ifdef WINDOWING
		delete mWindow;
		glfwTerminate();
#endif
	}
	void viewport::update() {
		mWindow->update();
	}
}
