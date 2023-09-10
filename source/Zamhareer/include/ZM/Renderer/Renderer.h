#pragma once

#include <vec2.hpp>

namespace ZM
{
	struct Settings
	{
		glm::vec2 RenderSize;
		glm::vec2 RenderPos;
	};

	template<class impl>
	class Renderer :public impl
	{
		public:
			Renderer(){}
			Renderer(Sittings s)
			 	:m_Sittings(s){}

			void Init()
			{
				impl::Init();
			}
			void Update()
			{
				impl::Update();
			}
			void Terminate()
			{
				impl::Terminate();
			}
			inline Settings &GetSittings(){return m_Sittings;}
			~Renderer()
			{
				Terminate();
			}
		private:
			Settings m_Sittings;

	}
}
