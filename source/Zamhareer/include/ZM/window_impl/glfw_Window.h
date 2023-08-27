#pragma once

#include "ZM/ViewPort.h"
#include <string>

struct GLFWwindow;

namespace ZM {
	class Window :public ViewPort
	{
		public:
			Window(const char *name, glm::vec2 size);
			virtual void Init() override;
			virtual void Refresh() override;
			virtual void Terminate() override;
			virtual void SetUpEventCallback() override;
		private:
			std::string m_Name;
			GLFWwindow *m_Handle;
	};
}
