#pragma once


#include<ZM/Layer.h>
#include <iostream>
class LayerA :public ZM::Layer
{
	public:
		LayerA(const char *n)
			:ZM::Layer(n){}
		virtual void Init() override{
		}
		virtual void Update() override{
		}
		virtual void OnEvent(ZM::Event &e) override{
		}
};
class LayerB :public ZM::Layer
{
	public:
		LayerB(const char *n)
			:ZM::Layer(n){}
		virtual void Init() override{
			OAA::Array<ZM::Vertex> verts = {{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0), glm::vec2(0)},
								{glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0), glm::vec2(0)},
								{glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(0), glm::vec2(0)}};
			OAA::Array<unsigned int> indces = {0, 1, 2};
			m_mesh = m_RendererRef->CreatMesh(verts, indces);
		}
		virtual void Update() override{
			m_RendererRef->DrawMesh(m_mesh);
		}
		virtual void OnEvent(ZM::Event &e) override{
		}
	private:
		ZM::Renderer * const m_RendererRef = ZM::Engine::GetInstance()->GetRenderer();
		void * m_mesh;
};
