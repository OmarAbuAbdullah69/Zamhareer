#include "ZM/window_impl/glfw_Window.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include"ZM/Engine.h"
#include "ZM/Event/MouseEvent.h"


namespace ZM {
	Engine *engine = Engine::GetInstance();

	Window::Window(const char *name, glm::vec2 size)
		:ViewPort(size), m_Name(name)
	{}
	void Window::Init()
	{
		assert(glfwInit());
		m_Handle = glfwCreateWindow(m_Size.x, m_Size.y, m_Name.c_str(), NULL, NULL);

		//Put the Engine pointer into the glfw datastruct
		glfwSetWindowUserPointer(m_Handle, engine);

		/* Make the window's context current */
    	glfwMakeContextCurrent(m_Handle);
		SetUpEventCallback();
	}
	void Window::Refresh()
	{
		/* Render here */
        glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
		
        /* Swap front and back buffers */
		glfwSwapBuffers(m_Handle);


        /* Poll for and process events */
        glfwPollEvents();
	}
	void Window::SetUpEventCallback()
	{
		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow *window, double xpos, double ypos)
				{
					Engine *e = (Engine *)glfwGetWindowUserPointer(window);
					MouseMoveEvent ev((float)xpos, (float)ypos); // there is an error here for some reasone
					e->OnEvent(ev);
				});
	}
	void Window::Terminate()
	{
		glfwTerminate();
	}
}
