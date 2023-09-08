#pragma once

#include "ZM/ViewPort.h"
#include <string>

struct GLFWwindow;

namespace ZM {
	template<class impl>
	class Window :public ViewPort,public impl
	{
		public:
			Window(const char *name, glm::vec2 size)
				:m_Name(name), ViewPort(size){}
			virtual void Init() override
			{
				impl::Init(m_Name.c_str(), GetSize());
				SetUpEventCallback();
			}
			virtual void Refresh() override
			{
				impl::Refresh(m_ClearColor);
			}
			virtual void SetUpEventCallback() override
			{
				impl::SetUpEventCallback();
			}
			virtual void Terminate() override
			{
				impl::Terminate();
			}
		private:
			std::string m_Name;
	};
	
}
