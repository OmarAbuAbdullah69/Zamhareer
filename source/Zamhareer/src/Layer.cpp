#include "ZM/Layer.h"

namespace ZM {
	Layer::Layer(const char * n)
		:m_Name(n)
	{

	}
	Layer::~Layer()
	{
	}
	void LayerStack::PushLayer(Layer *l)
	{
		m_Layers.PushBack(l);	
	}
	void LayerStack::Init()
	{
		for(Layer *l : m_Layers) {
			l->Init();
		}
	}
	void LayerStack::Update(double delta)
	{
		for(Layer *l : m_Layers) {
			l->Update(delta);
		}
	}
	void LayerStack::OnEvent(Event &e)
	{
		for(int i = m_Layers.Length()-1; i>=0 ;i--){
			m_Layers[i]->OnEvent(e);
		}
	}
	LayerStack::~LayerStack()
	{
		for(Layer *l :m_Layers){
			delete l;
		}
	}
}
