#pragma once

#include"Event.h"
#include<vec2.hpp>
namespace ZM {
	class WindowResizeEvent :public Event
	{
		public:
			WindowResizeEvent(unsigned width, unsigned height)
				:m_Size(width, height){}
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::WindowResize;}

			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"Window Size = ("<<m_Size.x <<", "<< m_Size.y<<" )\n";
			}
			#endif // DEBUG
			inline glm::vec2 GetSize() const {return m_Size;}	
		private:
			glm::vec2 m_Size;
	};
	class WindowMoveEvent :public Event
	{
		public:
			WindowMoveEvent(int xpos, int ypos)
				:m_Pos(xpos, ypos){}
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::WindwoMove;}

			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"Window Pos = ("<<m_Pos.x <<", "<< m_Pos.y<<" )\n";
			}
			#endif // DEBUG

		private:
			glm::vec2 m_Pos;
	};
	class WindowCloseEvent :public Event
	{
		public:
			WindowCloseEvent(){}
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::WindowClose;}

			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"Window Close\n";
			}
			#endif // DEBUG
	};
}//ZM
