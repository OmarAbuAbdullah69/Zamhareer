#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "event/event.hpp"

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
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	   			
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);	   			
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

			void set_event_callback(void(*event_callback)(const event &));
			void link_event_callback();
			
			// glfw only
			GLFWwindow *m_handle;
			int m_parent;
			bool m_opened = true;

			void (*m_event_callback)(const event &);

			void set_size(unsigned width, unsigned height);
			void get_size(unsigned &width, unsigned &height) const;
			
			void set_pos(unsigned posx, unsigned posy);
			void get_pos(unsigned &posx, unsigned &posy) const;

			static window *s_current;
			static std::vector<window> s_windows;
			static window_id s_creat_window(const char *name, unsigned width, unsigned height, window_id parent) {
				s_windows.push_back(window(name, width, height, parent));
				return s_windows.size();
			}

	};
}
