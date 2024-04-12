#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
namespace zm {
    typedef int window_id;

	class window {
		friend class core;
		friend class std::vector<window>;
		public:
			~window();
		private:
			window(const char * name, unsigned width, unsigned height, window_id parent);
			void update();
			void close();
			
			// glfw only
			GLFWwindow* m_Handle;
			static bool s_glfw_init;

			bool m_opened = true;
			window_id m_parent;

			static std::vector<window> s_windows;
			static window_id s_creat_window(const char *name, unsigned width, unsigned height, window_id parent) {
				s_windows.push_back(window(name, width, height, parent));
				return s_windows.size();
			}

	};
}
