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
		if(m_ViewPort){
			m_ViewPort->Init();
			m_ViewPort->SetRenderCall([]()
				{
					Engine::GetInstance()->GetRenderer()->Update();
				});}
		if(m_Renderer)
			m_Renderer->Init();

		m_LayerStack.Init();
	}
	


	void Engine::Update(){
		m_LayerStack.Update();
		if(m_ViewPort)
			m_ViewPort->Refresh();
		if(m_Renderer)
			m_Renderer->Init();
	}
	
	void Engine::OnEvent(Event& e)
	{
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
		if(m_Renderer)
			m_Renderer->Init();
	}


}
