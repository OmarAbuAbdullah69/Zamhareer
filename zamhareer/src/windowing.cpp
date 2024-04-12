#include "windowing.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>


namespace zm {
	
	bool window::s_glfw_init = false;
	std::vector<window> s_windows;
	
	window::window(const char * name, unsigned width, unsigned height, window_id parent) {
		if(!s_glfw_init) {
			glfwInit();
			#ifdef DEB_BUILD
			std::cout << "initlizing GLFW";
			#endif		
		} else {
			throw std::runtime_error("couldn't inilize GLFW");
		}
		// you should add parenting later
		m_Handle = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if(!m_Handle) {
			throw std::runtime_error("couldn't creat window");
		}
		gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		glfwMakeContextCurrent(m_Handle);
	}
	window::~window() {
		close();
	}
	void window::close() {
		m_opened = false;
		glfwDestroyWindow(m_Handle);
    	glfwTerminate();
	}
	void window::update() {
		//if(!m_opened) {
		//	throw std::runtime_error("unable to update the window is closed");
		//}
		m_opened = !glfwWindowShouldClose(m_Handle);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        /* Swap front and back buffers */
        glfwSwapBuffers(m_Handle);
        /* Poll for and process events */
        glfwPollEvents();


	}
}
