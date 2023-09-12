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
		}
		virtual void Update() override{
		}
		virtual void OnEvent(ZM::Event &e) override{
		}
};
