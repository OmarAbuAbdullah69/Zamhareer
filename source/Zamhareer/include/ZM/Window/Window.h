#pragma once

#include "ZM/ViewPort.h"
#include "ZM/oaa_String.h"

namespace ZM {
	enum WindowMode 
	{
		UnResizeable = 1 << 0,
		FullScreen = 1 << 1,
		NoTitleBar = 1 << 2,
	};


	template<class impl>
	class Window :public ViewPort,public impl
	{
		public:
			Window(const char *name, glm::vec2 size, int modes)
				:ViewPort(size), m_Name(name), m_Modes(modes){}
			virtual void Init() override
			{
				impl::Init(m_Name.cstr(), GetSize(), m_Modes);
				SetUpEventCallback();
			}
			virtual void Refresh() override
			{
				impl::Clear(m_ClearColor);
			}
			virtual void Draw() override
			{
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
			int m_Modes;
	};
	
}
