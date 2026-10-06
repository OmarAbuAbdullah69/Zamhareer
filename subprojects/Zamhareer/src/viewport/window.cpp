#include "zm/viewport/window.hpp"
#include "zm/logger.hpp"
#include <GLFW/glfw3.h>
namespace zm {
	window::window(const char *title, int width, int height) 
		:mTitle(title), mWidth(width), mHeight(height){
		glfwSetErrorCallback([](int code, const char *desc) {
					logger::inst().logError("glfwError code : {%0}\n{%1}", code, desc);
			exit(1);
				});
		mHandle = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if(!mHandle) {
			logger::inst().logError("couldn't make a Glfw window with name = {%0}, width = {%1}, height = {%2}", mTitle, mWidth, mHeight);
			exit(1);
		}
		logger::inst().logInfo("a Glfw window was made with name = {%0}, width = {%1}, height = {%2}", mTitle, mWidth, mHeight);
		glfwMakeContextCurrent(mHandle);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	window::~window() {
		glfwDestroyWindow(mHandle);
  	glfwTerminate();
	}
	void window::update() {
		glfwSwapBuffers(mHandle);
		glfwPollEvents();
		// back buffer is undefined after a swap; clear it so the next frame starts clean
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void window::setTitle(const char *title) {
		mTitle = title;
	}
	void window::setWidth(int width) {
		mWidth = width;
	}
	void window::setheight(int height) {
		mHeight = height;
	}
}
