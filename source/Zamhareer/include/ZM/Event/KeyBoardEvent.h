#pragma once

#include "Event.h"
#include "ZM/KeyCode.h"

namespace ZM {
	class KeyEvent: public Event
	{
		public:
			inline int GetKeyCode() const {return m_KeyCode;}
		protected:
			KeyEvent(int code)
				:m_KeyCode(code){}
		private:
			int m_KeyCode;
	};

	class KeyPressEvent :public KeyEvent
	{
		public:
			KeyPressEvent(int code, int repeat)
				:KeyEvent(code), m_Repeat(repeat){}
			
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::KeyPress;}

			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"Key Pressed Code = "<< GetKeyCode() << ", repeat = "<< m_Repeat << '\n';
			}
			#endif // DEBUG
			 
			inline int GetRepeatCount() const {return m_Repeat;}
		private:
			int m_Repeat;
	};
	class KeyReleaseEvent :public KeyEvent
	{
		public:
			KeyReleaseEvent(int code)
				:KeyEvent(code){}
			
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::KeyRelease;}

			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"Key Release Code = "<< GetKeyCode() << '\n';
			}
			#endif // DEBUG
			
	};
	class CharacterTypeEvent :public Event
	{
		public:
			CharacterTypeEvent(unsigned int character)
				:m_Character(character){}
			virtual EventType GetEventType(){return GetStaticType();}
			static EventType GetStaticType(){return EventType::CharacterEvent;}

			#ifdef DEBUG_MODE
			virtual void ToString()
			{
				std::cout <<"character typed = "<< m_Character << '\n';
			}
			#endif // DEBUG
		private:
			unsigned int m_Character;
	};
}
