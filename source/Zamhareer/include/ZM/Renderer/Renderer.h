#pragma once

#include <glm/glm.hpp>

#include "ZM/oaa_Array.h"
#include "ZM/Image.h"

namespace ZM
{	
	struct Vertex
	{
		glm::vec4 Pos;
		glm::vec3 Norm;
		glm::vec2 UV;
	};
	struct Material
	{
		Image Albedo;
	};
	struct Settings
	{
		glm::vec2 RenderSize;
		glm::vec2 RenderPos;
		
		bool GammaCorrection;
	};

	class Renderer
	{
		public:
			Renderer(Settings s)
				:m_Settings(s){}
			virtual ~Renderer(){}

			virtual void Init() = 0;
			virtual void Terminate() = 0;

			virtual void *CreatMesh(OAA::Array<Vertex> &verts, OAA::Array<unsigned int> &indices, const Material &mat) = 0;
			virtual void DrawMesh(void *data, glm::mat4 transform, glm::mat4 ViewPorject) = 0;
			inline Settings &GetSettings(){return m_Settings;}
			virtual void ResetSettings() = 0;
		protected:
			Settings m_Settings;

	};
}
