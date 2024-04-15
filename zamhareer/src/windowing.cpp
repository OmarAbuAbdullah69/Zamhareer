#include "windowing.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>


namespace zm {
	
	std::vector<window> s_windows;
	
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
		glfwMakeContextCurrent(m_handle);

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
