#include "ZM/Engine.h"

#include <iostream>

#include "ZM/Event/WindowEvent.h"
#include "ZM/Event/KeyBoardEvent.h"
#include "ZM/Event/MouseEvent.h"

namespace ZM {
	Engine *Engine::m_Instance = nullptr;
	Engine::Engine(){
		assert(!m_Instance);
		m_Instance = this;
	}
	void Engine::Init(){
		m_LayerStack.Init();
		if(m_ViewPort)
			m_ViewPort->Init();
	}
	


	void Engine::Update(){
		m_LayerStack.Update();
		if(m_ViewPort)
			m_ViewPort->Refresh();
	}
	
	void Engine::OnEvent(Event& e)
	{
	#ifdef DEBUG_MODE
		e.ToString();
	#endif // DEBUG
		EventDispatcher dis(e);
		dis.Dispatch<WindowCloseEvent>([](WindowCloseEvent &e){
				Engine::GetInstance()->Close();
				return true;});
		m_LayerStack.OnEvent(e);
	}
	
	void Engine::Terminate()
	{
		if(m_ViewPort)
			m_ViewPort->Terminate();
	}


}
