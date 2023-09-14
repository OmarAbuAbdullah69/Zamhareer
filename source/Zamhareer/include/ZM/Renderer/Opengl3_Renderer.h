#pragma once
#include "Renderer.h"
namespace ZM
{
	class OGL3_Renderer:public Renderer
	{
		public:
			OGL3_Renderer(Settings s);
			virtual void Init() override;
			virtual void Update() override;
			virtual void Terminate() override;
	
			void *CreatMesh(OAA::Array<Vertex> verts, OAA::Array<unsigned int> indices);
	};
	
}
