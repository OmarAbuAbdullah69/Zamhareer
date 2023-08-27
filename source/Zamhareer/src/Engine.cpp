#include "ZM/Engine.h"

namespace ZM {
	Engine *Engine::m_Instance = nullptr;
	Engine::Engine(){
		assert(!m_Instance);
		m_Instance = this;
	}
	void Engine::Init(){
		if(m_ViewPort)
			m_ViewPort->Init();
	}
	


	void Engine::Update(){
		if(m_ViewPort)
			m_ViewPort->Refresh();
	}
	
	void Engine::OnEvent(Event& e)
	{
	#ifdef DEBUG_MODE
		e.ToString();
	#endif // DEBUG
	}

	void Engine::Terminate()
	{
		if(m_ViewPort)
			m_ViewPort->Terminate();
	}


}
