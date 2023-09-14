#pragma once

#include <vec2.hpp>
#include <vec3.hpp>

#include <ZM/oaa_Array.h>

namespace ZM
{	
	struct Vertex
	{
		glm::vec3 Pos;
		glm::vec2 Norm;
		glm::vec2 UV;
	};
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

			virtual void *CreatMesh(OAA::Array<Vertex> verts, OAA::Array<unsigned int> indices) = 0;

			inline Settings &GetSittings(){return m_Settings;}
		private:
			Settings m_Settings;

	};
}
