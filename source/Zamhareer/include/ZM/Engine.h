#pragma once
#include "ViewPort.h"
#include "Layer.h"
#include "Renderer/Renderer.h"

namespace ZM {
	class Engine
	{
		public:
			Engine();
			~Engine();
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
			
			template<class R>
			void SetRenderer(Settings s)
			{ 
				m_Renderer = new R(s);
			}
			inline Renderer *GetRenderer() {return m_Renderer;}
		private:
			bool m_Close = false;
			float m_Time;
			
			LayerStack m_LayerStack;
			static Engine *m_Instance;
			ViewPort *m_ViewPort;
			Renderer *m_Renderer;

	};
}
