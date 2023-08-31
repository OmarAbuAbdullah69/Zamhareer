#pragma once

#include "Event/Event.h"
#include <string>
#include "Orray.h"

namespace ZM {
	class Layer
	{
		public:
			Layer(const char * n);
			virtual ~Layer();
			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual void OnEvent(Event &e) = 0;

			std::string GetName() const {return m_Name;}
		private:
			std::string m_Name;
	};
	class LayerStack
	{
		public:
			~LayerStack();
			void PushLayer(Layer *l);
			void Init();
			void Update();
			void OnEvent(Event &e);
		private:
			Orray<Layer *> m_Layers;	
	};
}
