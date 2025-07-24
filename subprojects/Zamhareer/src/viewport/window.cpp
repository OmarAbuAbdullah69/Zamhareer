#include "zm/viewport/window.hpp"
#include "zm/logger.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
namespace zm {
	window::window(const char *title, int width, int height) 
		:mTitle(title), mWidth(width), mHeight(height){
		mHandle = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if(!mHandle) {
			logger::inst().logError("couldn't make a Glfw window with name = {%0}, width = {%1}, height = {%2}", mTitle, mWidth, mHeight);
			exit(1);
		}
		logger::inst().logInfo("a Glfw window was made with name = {%0}, width = {%1}, height = {%2}", mTitle, mWidth, mHeight);
		glfwMakeContextCurrent(mHandle);
	}
	window::~window() {
		glfwDestroyWindow(mHandle);
	}
	void window::update() {
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mHandle);
		glfwPollEvents();
	}
	std::string window::getTitle() const {
		return mTitle;
	}
	int window::getWidth() const {
		return mWidth;
	}
	int window::getHeight() const {
		return mHeight;
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
