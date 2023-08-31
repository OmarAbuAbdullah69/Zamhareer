#pragma once
#include "ViewPort.h"
#include <iostream>
#include "Layer.h"
namespace ZM {
	class Engine
	{
		public:
			Engine();
			virtual void Init();
			virtual void Update();
			virtual void OnEvent(Event& e);
			virtual void Terminate();

			template<class L>
			void PushBackLayer(const char *n)
			{
				L *l = new L(n);
				m_LayerStack.PushLayer(l);
			}
		
			inline float GetTime() const {return m_Time;}
			static Engine *GetInstance() {return m_Instance;}
			inline void SetViewPort(ViewPort * v){m_ViewPort = v;}
			inline bool ShouldClose() const  {return m_Close;}
			inline void Close() {m_Close = true;}
		private:
			LayerStack m_LayerStack;
			static Engine *m_Instance;
			ViewPort *m_ViewPort;
			float m_Time;
			bool m_Close = false;

	};
}
