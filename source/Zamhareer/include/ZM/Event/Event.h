#pragma once

namespace ZM {
	enum EventType {
		None = 0,
		//Window
		WindowResize, WindwoMove,
		//Input
		KeyRelease, KeyPress,
		//Mouse
		MouseMove, MouseButton, MouseScroll,
		//Applecation
		AppStart, AppClose, AppTick
	};


	class Event
	{
		friend class EventDispatcher;
		public:
			virtual EventType GetEventType() = 0;
			#ifdef DEBUG_MODE
			virtual void ToString() = 0;
			#endif // DEBUG
			inline bool IsHandled() const {return m_Handled;}
		private:
			bool m_Handled;
	};

	class EventDispatcher
	{
		public:
			EventDispatcher(Event &e)
				:m_Event(e){}
			template<typename T>
				void Dispatch(void(*func)(T&))
				{
					if(m_Event.GetEventType() == T::GetStaticType())
					{
						m_Event.m_Handled = func(*((T *)&m_Event)); 
					}
				}
		private:
			Event& m_Event;
	};
}
