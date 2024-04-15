#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
namespace zm {
    typedef unsigned window_id;

	//only for glfw
	class glfw_term {
		friend class window;
		public:
			~glfw_term() {
				glfwTerminate();
#ifdef DEB_BUILD
				std::cout << "GLFW terminated " << std::endl;
#endif // DEBUG
			}
		private:
			glfw_term() {
				if(!glfwInit())
					throw std::runtime_error("couldn't initlize GLFW");
#ifdef DEB_BUILD
				std::cout << "GLFW initlized " << std::endl;
#endif // DEBUG

			}
	};


	class window {
		friend class core;
		//friend class std::vector<window>;
		public:
			window(window &&o);
			~window();
		private:
			window(const char * name, unsigned width, unsigned height, window_id parent);
			void update();
			void close();
			
			// glfw only
			GLFWwindow *m_handle;

			int m_parent;
			bool m_opened = true;

			void set_size(unsigned width, unsigned height);
			void get_size(unsigned &width, unsigned &height) const;
			
			void set_pos(unsigned posx, unsigned posy);
			void get_pos(unsigned &posx, unsigned &posy) const;

			static std::vector<window> s_windows;
			static window_id s_creat_window(const char *name, unsigned width, unsigned height, window_id parent) {
				s_windows.push_back(window(name, width, height, parent));
				std::cout << "window moved before\n";
				return s_windows.size();
			}

	};
}
