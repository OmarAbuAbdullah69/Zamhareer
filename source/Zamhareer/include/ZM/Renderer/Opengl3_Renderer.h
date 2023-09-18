#pragma once
#include "Renderer.h"
namespace ZM
{
	struct MeshData
	{
		unsigned int VAO, VBO, EBO;
		unsigned int count;
		unsigned int ShaderProgram;
	};
	class OGL3_Renderer:public Renderer
	{
		public:
			OGL3_Renderer(Settings s);
			virtual void Init() override;
			virtual void Terminate() override;
	
			virtual void *CreatMesh(OAA::Array<Vertex> &verts, OAA::Array<unsigned int> &indices)override;
			virtual void DrawMesh(void *data);
			virtual void ResetSettings();
	};
	
}
