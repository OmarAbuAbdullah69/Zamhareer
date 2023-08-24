#pragma once
#include"vec3.hpp"

namespace ZM{
	class ViewPort{
		public:
			virtual void ReFresh(glm::vec3 color) = 0;
		protected:
			glm::vec2 m_Size;
	};
}
