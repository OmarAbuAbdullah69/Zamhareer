#pragma once
#include "ViewPort.h"

namespace ZM {
	class Engine
	{
		public:
			Engine();
			virtual void Init();
			virtual void Update();
			virtual void OnEvent(Event& e);
			virtual void Terminate();
			
			inline float GetTime() const {return m_Time;}
			static Engine *GetInstance() {return m_Instance;}
			inline void SetViewPort(ViewPort * v){m_ViewPort = v;}
			inline bool ShouldClose() const  {return m_Close;}
		private:
			static Engine *m_Instance;
			ViewPort *m_ViewPort;
			float m_Time;
			bool m_Close = false;

	};
}
