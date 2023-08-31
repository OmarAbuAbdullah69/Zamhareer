#pragma once


#include<ZM/Layer.h>
#include <iostream>
class LayerA :public ZM::Layer
{
	public:
		LayerA(const char *n)
			:ZM::Layer(n){}
		virtual void Init() override{
			std::cout << "class A init"<<" by "<<GetName() << std::endl;
		}
		virtual void Update() override{
			// std::cout << "class A Update"<<" by "<<GetName() << std::endl;
		}
		virtual void OnEvent(ZM::Event &e) override{
			std::cout << "class A OnEvent"<<" by "<<GetName() << std::endl;
			e.ToString();
		}
};
class LayerB :public ZM::Layer
{
	public:
		LayerB(const char *n)
			:ZM::Layer(n){}
		virtual void Init() override{
			std::cout << "class B init"<<" by "<<GetName() << std::endl;
		}
		virtual void Update() override{
			// std::cout << "class B Update"<<" by "<<GetName() << std::endl;
		}
		virtual void OnEvent(ZM::Event &e) override{
			std::cout << "class B OnEvent"<<" by "<<GetName() << std::endl;
			e.ToString();
		}
};
