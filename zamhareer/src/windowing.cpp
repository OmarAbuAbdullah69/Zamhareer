#include "windowing.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>


namespace zm {
	
	bool window::s_glfw_init = false;
	std::vector<window> s_windows;
	
	window::window(const char * name, unsigned width, unsigned height, window_id parent)
		: m_width(width), m_height(height){
	
		// dies at the exit of the program
		static glfw_term gt;

		if(!s_glfw_init) {
			if(!glfwInit()) {
				throw std::runtime_error("faild to initlize GLFW");
			}
			window::s_glfw_init = true;
			#ifdef DEB_BUILD
			std::cout << "initlizing GLFW\n";
			#endif		
		}
		// you should add parenting later
		m_handle = glfwCreateWindow(width, height, name, NULL, NULL);
		if(!m_handle) {
			throw std::runtime_error("couldn't creat window");
		}
		int posx, posy;
		glfwGetWindowPos(m_handle, &posx, &posy);
		m_posx = posx;
		m_posy = posy;
#ifdef DEB_BUILD
		std::cout << "window created with : " << m_handle << std::endl
			<< "size: (" << m_width << ", " << m_height << " )" << std::endl
			<< "pos: (" << m_posx << ", " << m_posy<< " )" << std::endl;
#endif // DEBUG
		glfwMakeContextCurrent(m_handle);

	}
	window::window(window &&o) {
#ifdef DEB_BUILD
		std::cout << "window object moved:" << m_handle << std::endl;
#endif // DEBUG
		m_handle = o.m_handle;
		m_parent = o.m_parent;
		m_opened = o.m_opened;

		o.m_handle = nullptr;
		o.m_opened = false;
		o.m_parent = 0;
	}
	window::~window() {
		close();
	}

	
	void window::set_pos(unsigned posx, unsigned posy) {
		glfwSetWindowPos(m_handle, m_posx, m_posy);
	}
	void window::set_size(unsigned width, unsigned height) {
		glfwSetWindowSize(m_handle, m_width, m_height);
	}
	

	void window::close() {
	   if (m_handle) {
#ifdef DEB_BUILD
			std::cout << "window object destroied: " << m_handle << std::endl;
#endif // DEBUG
			m_opened = false;
			glfwDestroyWindow(m_handle);
		}
	}
	void window::update() {
		if(!m_opened) {
			throw std::runtime_error("unable to update the window is closed");
		}
	
		glfwMakeContextCurrent(m_handle);		

		m_opened = !glfwWindowShouldClose(m_handle);
        /* Render here */
    	glClear(GL_COLOR_BUFFER_BIT);
        /* Swap front and back buffers */
        glfwSwapBuffers(m_handle);
        /* Poll for and process events */
        glfwPollEvents();


	}
}
