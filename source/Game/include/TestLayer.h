#pragma once

#include <ZM/Camera2D.h>
#include <ZM/Layer.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <ZM/Node.h>
#include <ZM/Event/KeyBoardEvent.h>
#include <glm/glm.hpp>


std::ostream &operator << (std::ostream &os, glm::mat4 m)
{
	os << '[' << std::endl;
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++)
		{
			os << m[i][j] << ", ";
		}
		os << std::endl;
	}
 	os<< ']'<< std::endl;
	return os;
}

glm::vec2 operator * (const glm::vec2 &v, const float &c)
{
	return glm::vec2(v.x*c, v.y*c);
}

class quad: public ZM::Node2D
{
	public:
		quad(const char *name, ZM::Node2D *parent = NULL);
		virtual void Init() override;
		virtual void Update(double delta) override;
		virtual void OnEvent(ZM::Event &event) override;
	private:
		ZM::Renderer * const m_RendererRef = ZM::Engine::GetInstance()->GetRenderer();
		void * m_mesh;
};

class _Camera:public ZM::Camera2D
{
	public:
		_Camera(const char *name, ZM::Node2D *parent)
			:ZM::Camera2D(name, parent, -1 ,1 , -1, 1){} 
		virtual void Init()
		{

		}
		virtual void Update(double delta)
		{
		}
		virtual void OnEvent(ZM::Event &event)
		{
			ZM::EventDispatcher dis(event);
			dis.Dispatch<ZM::KeyPressEvent>([](ZM::KeyPressEvent &e){
					switch (e.GetKeyCode()) {
							case(ZM_KEY_W):
							{
								break;
							}
							
						}
						return true;
						});
		}
	private:
		bool left, right, up, down;
};

class LayerA :public ZM::Layer
{
	public:
		static ZM::Camera2D *CurrentCamera;
		LayerA(const char *n);
		virtual void Init() override;
		virtual void Update(double delta) override;
		virtual void OnEvent(ZM::Event &e) override;
	private:
		ZM::Node2D m_RootNode;
};

ZM::Camera2D *LayerA::CurrentCamera = nullptr;

LayerA::LayerA(const char *n)
	:ZM::Layer(n), m_RootNode("Root"){}
void LayerA::Init()
{
	quad *new_node = new quad("quad", &m_RootNode);
	m_RootNode.Init();
	new_node->Scale(glm::vec2(0.3, 0.3));
	_Camera *cam = new _Camera("first cam", &m_RootNode);
	CurrentCamera = cam;
	std::cout << new_node->GetTransform() << std::endl;
}
void LayerA::Update(double delta)
{
	static double time = 0;
	m_RootNode.Rotate(3.1415*delta);
	m_RootNode.Translate(glm::vec2(std::sin(time)*delta, 0.0));
	m_RootNode.Update(delta);
	time += delta;
}
void LayerA::OnEvent(ZM::Event &e)
{
	m_RootNode.OnEvent(e);
}

quad::quad(const char *name, ZM::Node2D *parent)
	:Node2D(name, parent){}
void quad::Init()
{
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
void quad::Update(double delta)
{
	m_RendererRef->DrawMesh(m_mesh, GetTransform(), LayerA::CurrentCamera->GetView());
}
void quad::OnEvent(ZM::Event &e)
{

}
