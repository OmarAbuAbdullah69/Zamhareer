#include "zm/viewport/viewport.hpp"
#if WINDOWING
#include "zm/logger.hpp"
#include <cstdlib>
namespace zm {
	window::window(const char *title, int width, int height) 
		:mTitle(title), mWidth(width), mHeight(height){
		mHandle = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if(!mHandle) {
			logger::inst().logError("couldn't make a Glfw window with name = {%0}, width = {%1}, height = {%2}", mTitle, mWidth, mHeight);
			std::exit(1);
		}
		logger::inst().logInfo("a Glfw window was made with name = {%0}, width = {%1}, height = {%2}", mTitle, mWidth, mHeight);
		glfwMakeContextCurrent(mHandle);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	window::~window() {
		glfwDestroyWindow(mHandle);
	}
	void window::update() {
		glfwSwapBuffers(mHandle);
		glfwPollEvents();
		// back buffer is undefined after a swap; clear it so the next frame starts clean
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void window::setTitle(const char *title) {
		mTitle = title;
		glfwSetWindowTitle(mHandle, title);
	}
	void window::setWidth(int width) {
		mWidth = width;
		glfwSetWindowSize(mHandle, mWidth, mHeight);
	}
	void window::setHeight(int height) {
		mHeight = height;
		glfwSetWindowSize(mHandle, mWidth, mHeight);
	}
}
#endif
