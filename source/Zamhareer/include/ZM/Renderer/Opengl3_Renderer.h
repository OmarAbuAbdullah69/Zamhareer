#pragma once
#include "Renderer.h"
namespace ZM
{
	class Texture
	{
		public:
			Texture();
			Texture(Image i);
			void Use();
		private:
			unsigned int m_ID;
	};
	struct MeshData
	{
		unsigned int VAO, VBO, EBO;
		unsigned int Count;
		unsigned int ShaderProgram;
		Texture *Textures;
		unsigned int TexturesCount;
	};
	class OGL3_Renderer:public Renderer
	{
		public:
			OGL3_Renderer(Settings s);
			virtual void Init() override;
			virtual void Terminate() override;
	
			virtual void *CreatMesh(OAA::Array<Vertex> &verts, OAA::Array<unsigned int> &indices, const Material &mat)override;
			virtual void DrawMesh(void *data);
			virtual void ResetSettings();
	};
	
}
