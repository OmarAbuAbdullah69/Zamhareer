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
				std::cout <<"MousePos = ("<<m_Pos.x <<", "<< m_Pos.y<<" )"<< std::endl;
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
				:m_Amount(x, y){}
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::MouseScroll;}
			
			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"MouseScroll = ("<<m_Amount.x <<", "<< m_Amount.y<<" )"<< std::endl;
			}
			#endif // DEBUG
			
			inline glm::vec2 GetAmount() const {return m_Amount;}
		private:
			glm::vec2 m_Amount;
	};
	class MouseButtonEvent :public Event
	{
		public:
			MouseButtonEvent(int button)
				:m_Button(button){}

			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::MouseButton;}
			
			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"MouseButton = ("<<m_Button<<" )"<< std::endl;
			}
			#endif // DEBUG
			
		private:
			int m_Button;	
	};
}
