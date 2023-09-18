#include "ZM/Engine.h"

#include "ZM/Event/WindowEvent.h"
#include "ZM/Event/KeyBoardEvent.h"
#include "ZM/Event/MouseEvent.h"

namespace ZM {
	Engine *Engine::m_Instance = nullptr;

	Engine::Engine(){
		assert(!m_Instance);
		m_Instance = this;
	}
	Engine::~Engine()
	{
		delete m_Renderer;
	}
	void Engine::Init(){
		if(m_ViewPort)
			m_ViewPort->Init();
		if(m_Renderer)
			m_Renderer->Init();

		m_LayerStack.Init();
	}
	
	void Engine::Update(){
		if(m_ViewPort)
			m_ViewPort->Refresh();
		m_LayerStack.Update();
		if(m_ViewPort)
			m_ViewPort->Draw();

	}
	
	void Engine::OnEvent(Event& e)
	{
		EventDispatcher dis(e);
		dis.Dispatch<WindowCloseEvent>([](WindowCloseEvent &e){
				Engine::GetInstance()->Close();
				return true;});

		dis.Dispatch<WindowResizeEvent>([](WindowResizeEvent &e){
				Settings &s = Engine::GetInstance()->GetRenderer()->GetSettings();
				s.RenderSize = e.GetSize();
				Engine::GetInstance()->GetRenderer()->ResetSettings();
				return true;
				});

		m_LayerStack.OnEvent(e);
	}
	
	void Engine::Terminate()
	{
		if(m_ViewPort)
			m_ViewPort->Terminate();
		if(m_Renderer)
			m_Renderer->Terminate();
	}


}
