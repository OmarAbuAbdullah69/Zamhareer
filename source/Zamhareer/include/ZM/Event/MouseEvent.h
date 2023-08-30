#pragma once

#include "Event.h"
#include "vec2.hpp"

namespace ZM {
	class MouseMoveEvent :public Event
	{
		public:
			MouseMoveEvent(float x, float y)
				:m_Pos(x, y){}
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::MouseMove;}

			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"Mouse Pos = ("<<m_Pos.x <<", "<< m_Pos.y<<" )\n";
			}
			#endif // DEBUG
			
			inline glm::vec2 GetPos() const {return m_Pos;}
		private:
			glm::vec2 m_Pos;
	};

	class MouseScrollEvent :public Event
	{
		public:
			MouseScrollEvent(float x, float y)
				:m_Offset(x, y){}
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::MouseScroll;}
			
			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"Mouse Scroll = ("<<m_Offset.x <<", "<< m_Offset.y<<" )\n";
			}
			#endif // DEBUG
			
			inline glm::vec2 GetOffset() const {return m_Offset;}
		private:
			glm::vec2 m_Offset;
	};
	class MouseButtonEvent :public Event
	{
		public:
			int GetButton() const {return m_Button;}
		protected:
			MouseButtonEvent(int button)
				:m_Button(button){}

		private:
			int m_Button;	
	};

	class MouseButtonPressEvent :public MouseButtonEvent
	{
		public:
			MouseButtonPressEvent(int button)
				:MouseButtonEvent(button){}
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::MouseButtonPress;}
			
			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"Mouse Button Press keycode= " << GetButton()<<'\n';
			}
			#endif
	};
	class MouseButtonReleaseEvent :public MouseButtonEvent
	{
		public:
			MouseButtonReleaseEvent(int button)
				:MouseButtonEvent(button){}
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::MouseButtonRelease;}
			
			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"Mouse Button Release keycode= " << GetButton()<< '\n';
			}
			#endif
	};
}
