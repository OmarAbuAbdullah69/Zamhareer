#pragma once

#include "ZM/Renderer/Renderer.h"

#include <vec4.hpp>
#include <vec2.hpp>

namespace ZM{

	class glfw_imple_window
	{
		protected:
			void Init(const char *name, glm::vec2 size, int modes);
			void Clear(glm::vec4 color);
			void ShowNPoll();
			void SetUpEventCallback();
			void Terminate();
		private:
			void *m_Handle;
	};

}
