#include "ZM/window_impl/glfw_Window.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <functional>


#include"ZM/Engine.h"
#include "ZM/Event/MouseEvent.h"


namespace ZM {

	Window::Window(const char *name, glm::vec2 size)
		:ViewPort(size), m_Name(name)
	{}
	void Window::Init()
	{
		assert(glfwInit());
		m_Handle = glfwCreateWindow(m_Size.x, m_Size.y, m_Name.c_str(), NULL, NULL);

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

		//Mouse Move
		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow *window, double xpos, double ypos)
				{
					assert(window);
					MouseMoveEvent ev(xpos, ypos); 
					Engine::GetInstance()->OnEvent(ev);
				});
		//Mouse Scroll
		glfwSetScrollCallback(m_Handle, [](GLFWwindow *window, double xoffset, double yoffset)
		{
			assert(window);
			MouseScrollEvent ev(xoffset, yoffset);
			Engine::GetInstance()->OnEvent(ev);
		});
		//Mouse Button
		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
				{
					assert(window)
				})
	}
	void Window::Terminate()
	{
		glfwTerminate();
	}
}
