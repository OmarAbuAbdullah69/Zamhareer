#include "ZM/Window/glfw_impl.h"


#include "ZM/Event/Event.h"
#include "ZM/Event/KeyBoardEvent.h"
#include "ZM/Event/MouseEvent.h"
#include "ZM/Event/WindowEvent.h"

#include "ZM/Engine.h"


namespace ZM{
	void glfw_imple_window::Init(const char *name, glm::vec2 size)
	{
		assert(glfwInit());
		m_Handle = glfwCreateWindow(size.x, size.y, name, NULL, NULL);

		/* Make the window's context current */
    	glfwMakeContextCurrent(m_Handle);
	}
	void glfw_imple_window::Refresh(glm::vec4 color)
	{
		
		/* Render here */
        glClearColor(color.x, color.y, color.z, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
		
        /* Swap front and back buffers */
		glfwSwapBuffers(m_Handle);


        /* Poll for and process events */
        glfwPollEvents();
	
	}
	void glfw_imple_window::SetUpEventCallback()
	{
		// Window Events
		//Window Resize
		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height){
				assert(window);
				WindowResizeEvent ev(width, height);
				Engine::GetInstance()->OnEvent(ev);
				});
		//Window Move
		glfwSetWindowPosCallback(m_Handle, [](GLFWwindow* window, int xpos, int ypos)
				{
				assert(window);
				WindowMoveEvent ev(xpos, ypos);	
				Engine::GetInstance()->OnEvent(ev);
				});
		//Window Close
		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
				{
				assert(window);
				WindowCloseEvent ev;
				Engine::GetInstance()->OnEvent(ev);
				});
		//Window Events
		//Keyboard Events
		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods){
				assert(window);
				scancode += 0;
				mods +=0;
				switch (action) {
				case GLFW_PRESS:
				{
					KeyPressEvent ev(key, 0);
					Engine::GetInstance()->OnEvent(ev);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent ev(key, 1);
					Engine::GetInstance()->OnEvent(ev);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent ev(key);
					Engine::GetInstance()->OnEvent(ev);
					break;
				}
				}
				});
		glfwSetCharCallback(m_Handle, [](GLFWwindow* window, unsigned int codepoint){
				assert(window);
				CharacterTypeEvent ev(codepoint); 
				Engine::GetInstance()->OnEvent(ev);
				});
		//Keyboard Events
		//Mouse Events
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
					mods +=0;
					assert(window);
					switch (action) {
					case GLFW_PRESS:
					{
						MouseButtonPressEvent ev(button);	
						Engine::GetInstance()->OnEvent(ev);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleaseEvent ev(button);	
						Engine::GetInstance()->OnEvent(ev);
						break;
					}
				}	
				});
		//Mouse Events

	}
	void glfw_imple_window::Terminate()
	{
		glfwTerminate();
	}
}
