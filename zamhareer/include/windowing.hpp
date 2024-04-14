#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
namespace zm {
    typedef int window_id;

	
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
			glfw_term()=default;
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
			static bool s_glfw_init;


			int m_parent;
			bool m_opened = true;
			void set_pos(unsigned posx, unsigned posy);
			inline void get_pos(unsigned &posx, unsigned &posy) const{
				posx = m_posx;
				posy = m_posy;
			}
			void set_size(unsigned width, unsigned height);
			inline void get_size(unsigned &width, unsigned &height) const{
				width = m_width;
				height = m_height;
			}
			unsigned m_width, m_height, m_posx, m_posy;

			static std::vector<window> s_windows;
			static window_id s_creat_window(const char *name, unsigned width, unsigned height, window_id parent) {
				s_windows.push_back(window(name, width, height, parent));
				return s_windows.size();
			}

	};
}
