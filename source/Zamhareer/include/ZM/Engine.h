#pragma once
#include "ViewPort.h"

namespace ZM {
	class Engine
	{
		public:
			Engine();
			void Init();
			void Update();
			inline float GetTime(){return m_Time;}
			inline void SetViewPort(ViewPort * v){m_ViewPort = v;}
		private:
			ViewPort *m_ViewPort
			float m_Time;

	};
}
