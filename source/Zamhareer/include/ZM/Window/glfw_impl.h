#pragma once

#include <GLFW/glfw3.h>

#include <vec4.hpp>
#include <vec2.hpp>

#include <iostream>

namespace ZM{

	class glfw_imple_window
	{
		protected:
			void Init(const char *name, glm::vec2 size);
			void Refresh(glm::vec4 color);
			void SetUpEventCallback();
			void Terminate();
		private:
			GLFWwindow *m_Handle;
	};

}
