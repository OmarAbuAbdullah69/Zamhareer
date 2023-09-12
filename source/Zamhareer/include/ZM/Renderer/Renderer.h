#pragma once

#include <vec2.hpp>

namespace ZM
{
	struct Settings
	{
		glm::vec2 RenderSize;
		glm::vec2 RenderPos;
	};

	class Renderer
	{
		public:
			Renderer(Settings s)
				:m_Settings(s){}
			virtual ~Renderer(){}

			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual void Terminate() = 0;
			inline Settings &GetSittings(){return m_Settings;}
		private:
			Settings m_Settings;

	};
}
