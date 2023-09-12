#include "ZM/Renderer/Opengl3_Renderer.h"

#include "vec3.hpp"
#include <glad/glad.h>

namespace ZM
{
	struct Vertex
	{
		glm::vec3 Pos;
	};

	OGL3_Renderer::OGL3_Renderer(Settings s)
		:Renderer(s)
	{
        glClearColor(color.x, color.y, color.z, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void OGL3_Renderer::Init()
	{

	}
	void OGL3_Renderer::Update()
	{
	}
	void OGL3_Renderer::Terminate()
	{

	}
}
