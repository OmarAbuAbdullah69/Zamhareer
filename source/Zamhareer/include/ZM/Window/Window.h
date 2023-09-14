#pragma once

#include "ZM/ViewPort.h"
#include "ZM/oaa_String.h"

struct GLFWwindow;

namespace ZM {
	template<class impl>
	class Window :public ViewPort,public impl
	{
		public:
			Window(const char *name, glm::vec2 size)
				:ViewPort(size), m_Name(name){}
			virtual void Init() override
			{
				impl::Init(m_Name.cstr(), GetSize());
				SetUpEventCallback();
			}
			virtual void Refresh() override
			{
				impl::Clear(m_ClearColor);
				if(Render)
					Render();
				impl::ShowNPoll();
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
			OAA::String m_Name;
	};
	
}
