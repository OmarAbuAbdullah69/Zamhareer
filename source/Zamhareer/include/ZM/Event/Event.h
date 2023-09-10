#pragma once

namespace ZM {
	enum EventType {
		None = 0,
		//Window
		WindowResize, WindwoMove, WindowClose, WindowDrop, 
		//Input
		 KeyPress, KeyRelease, CharacterEvent,
		//Mouse
		MouseMove, MouseButtonPress, MouseButtonRelease, MouseScroll,
		//Applecation
		AppTick,
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
				void Dispatch(bool(*func)(T&))
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
