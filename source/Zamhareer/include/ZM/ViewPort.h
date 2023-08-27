#pragma once

#include<vec4.hpp>
#include<vec2.hpp>
#include"ZM/Event/Event.h" 


namespace ZM{
	class ViewPort{
		public:
			ViewPort(glm::vec2 size)
				:m_Size(size) {}
			virtual void Init() = 0;
			virtual void Refresh() = 0;
			virtual void Terminate() = 0;
			
			inline glm::vec2 GetSize() const {return m_Size;}
			inline void SetSize(glm::vec2 s){m_Size = s;}

			inline glm::vec4 GetColor() const {return m_ClearColor;}
			inline void SetColor(glm::vec4 c){m_ClearColor = c;}

		protected:
			virtual void SetUpEventCallback() = 0;
			glm::vec4 m_ClearColor = glm::vec4(1.0, 0.0, 1.0, 1.0);
			glm::vec2 m_Size;
	};
}
