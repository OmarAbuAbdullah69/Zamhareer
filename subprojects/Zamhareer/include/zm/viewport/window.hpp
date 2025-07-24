#pragma once

#include <string>
#include "GLFW/glfw3.h"
namespace zm {
	class viewport;
	class window {
		friend class viewport;
		private:
			window(const char *title, int width, int height);
			~window();
			void update();
			std::string getTitle() const;
			int getWidth() const;
			int getHeight() const;
			void setTitle(const char *title);
			void setWidth(int width);
			void setheight(int height);
		private:
			std::string mTitle;
			int mWidth, mHeight;
			GLFWwindow *mHandle;
	};
}
