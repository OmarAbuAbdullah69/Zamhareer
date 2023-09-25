#pragma once


#include <ZM/Layer.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


class LayerA :public ZM::Layer
{
	public:
		LayerA(const char *n)
			:ZM::Layer(n){}
		virtual void Init() override{
		}
		virtual void Update(double delta) override{
		}
		virtual void OnEvent(ZM::Event &e) override{
		}
	private:

};
class LayerB :public ZM::Layer
{
	public:
		LayerB(const char *n)
			:ZM::Layer(n){}
		virtual void Init() override{
			OAA::Array<ZM::Vertex> verts = {{glm::vec4(1.0, 1.0, 0, 1), glm::vec3(0), glm::vec2(1.0 ,1.0)},
								{glm::vec4(-1.0, 1.0, 0, 1), glm::vec3(0), glm::vec2(0.0, 1.0)},
								{glm::vec4(-1.0, -1.0, 0, 1), glm::vec3(0), glm::vec2(0.0, 0.0)},
								{glm::vec4(1.0, -1.0, 0, 1), glm::vec3(0), glm::vec2(1.0, 0.0)}};
			OAA::Array<unsigned int> indces = {0, 1, 2, 0, 2, 3};

			int staterr;
			ZM::Material mat = {
				.Albedo = ZM::LoadImage("resources/Images/image.png", &staterr)
			};
			if(staterr)
			{
				std::cout << "faild loading image" << std::endl;
			}
			m_mesh = m_RendererRef->CreatMesh(verts, indces, mat);
		}
		virtual void Update(double delta) override{
			m_RendererRef->DrawMesh(m_mesh, glm::mat4(1.0), glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.5, 1.0)));
		}
		virtual void OnEvent(ZM::Event &e) override{
		}
	private:
		ZM::Renderer * const m_RendererRef = ZM::Engine::GetInstance()->GetRenderer();
		void * m_mesh;
};
