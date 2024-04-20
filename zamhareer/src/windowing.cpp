#include "windowing.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

#include "event/key_event.hpp"
#include "event/keyboard_event.hpp"
#include "event/window_event.hpp"
#include "event/mouse_event.hpp"

namespace zm {
	
	window *window::s_current;
	std::vector<window> window::s_windows;
	window::window(const char * name, unsigned width, unsigned height, window_id parent) {
	
		// dies at the exit of the program
		static glfw_term gt;

		// you should add parenting later
		m_handle = glfwCreateWindow(width, height, name, NULL, NULL);
		if(!m_handle) {
			throw std::runtime_error("couldn't creat window");
		}
#ifdef DEB_BUILD
		int posx, posy;
		glfwGetWindowPos(m_handle, &posx, &posy);

		std::cout << "window created with : " << m_handle << std::endl
			<< "for object: " << this << std::endl
			<< "size: (" << width << ", " << height << " )" << std::endl
			<< "pos: (" << posx << ", " << posy<< " )" << std::endl;
#endif // DEBUG
	   	link_event_callback();
		glfwMakeContextCurrent(m_handle);
		gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

#ifdef DEB_BUILD
		glad_glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

#endif // DEBUG

	}
	window::window(window &&o) {
#ifdef DEB_BUILD
		std::cout << "window object moved: " << &o << std::endl;
		std::cout << "to : " << this << std::endl;
#endif // DEBUG
		m_handle = o.m_handle;
		m_parent = o.m_parent;
		m_opened = o.m_opened;

		o.m_handle = nullptr;
		o.m_opened = false;
		o.m_parent = 0;
	}
	window::~window() {
		std::cout << "window object destroied: " << this << std::endl;
		close();
	}

	
	void window::set_size(unsigned width, unsigned height) {
		glfwSetWindowSize(m_handle, width, height);
	}
	void window::get_size(unsigned &width, unsigned &height) const{
		glfwGetWindowSize(m_handle, (int *)&width, (int *)&height);
	}

	void window::set_pos(unsigned posx, unsigned posy) {
		glfwSetWindowPos(m_handle, posx, posy);
	}
	void window::get_pos(unsigned &posx, unsigned &posy) const{
		glfwGetWindowPos(m_handle, (int *)&posx, (int *)&posy);
	}

	

	void window::close() {
	   if (m_opened) {
#ifdef DEB_BUILD
			std::cout << "window destroied: " << m_handle << std::endl;
			std::cout << "for object: " << this << std::endl;
#endif // DEBUG
			m_opened = false;
			glfwDestroyWindow(m_handle);
			m_handle = nullptr;
		}
	}
	void window::update() {
		if(!m_opened) {
			throw std::runtime_error("unable to update the window is closed");
		}
		window::s_current = this;
		glfwMakeContextCurrent(m_handle);		

		m_opened = !glfwWindowShouldClose(m_handle);
        /* Render here */
    	glad_glClear(GL_COLOR_BUFFER_BIT);
        /* Swap front and back buffers */
        glfwSwapBuffers(m_handle);
        /* Poll for and process events */
        glfwPollEvents();
	}

	void window::set_event_callback(void(*event_callback)(const event &)) {
		s_current = this;
		m_event_callback = event_callback;
		link_event_callback();
	}
	void window::link_event_callback() {
		if(!m_event_callback)
			return;

		glfwSetWindowSizeCallback(m_handle, [](GLFWwindow *window, int width, int height) {
				window::s_current->m_event_callback(window_resize_event(width, height));
				});	
		glfwSetWindowPosCallback(m_handle, [](GLFWwindow *window, int posx, int posy) {
				window::s_current->m_event_callback(window_repos_event(posx, posy));
				});
		glfwSetCursorPosCallback(m_handle, [](GLFWwindow *window, double posx, double posy) {
				window::s_current->m_event_callback(mouse_move_event(posx, posy));
				});
		glfwSetScrollCallback(m_handle, [](GLFWwindow* window, double xoffset, double yoffset) {
				window::s_current->m_event_callback(mouse_scroll_event(xoffset, yoffset));
				});
		glfwSetMouseButtonCallback(m_handle, [](GLFWwindow* window, int button, int action, int mods) {
				switch (action) {
					case ZM_PRESS: {
						window::s_current->m_event_callback(mouse_button_press_event(button, mods));
						break;
					}
					case ZM_RELEASE: {
						window::s_current->m_event_callback(mouse_button_release_event(button, mods));
						break;
					}
				}
				});
		glfwSetKeyCallback(m_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
					switch (action) {
					case ZM_PRESS: {
						window::s_current->m_event_callback(key_press_event(key, mods));
						break;
					}
					case ZM_RELEASE: {
						window::s_current->m_event_callback(key_release_event(key, mods));
						break;
					}
					case ZM_KEY_DOWN: {
						window::s_current->m_event_callback(key_down_event(key, mods));
						break;
					}
				}
				});
		glfwSetCharCallback(m_handle, [](GLFWwindow* window, unsigned int codepoint) {
				window::s_current->m_event_callback(char_type_event(codepoint));
				});
	}
}
