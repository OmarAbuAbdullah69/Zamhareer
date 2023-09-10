#pragma once

#include "Event/Event.h"
#include "ZM/oaa_String.h"

#define OAA_ARRAY_IMPL 
#include "oaa_Array.h"

namespace ZM {
	class Layer
	{
		public:
			Layer(const char * n);
			virtual ~Layer();
			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual void OnEvent(Event &e) = 0;

			const char *GetName() {return m_Name.cstr();}
		private:
			OAA::String m_Name;
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
			OAA::Array<Layer *> m_Layers;	
	};
}
