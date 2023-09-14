#include "ZM/Renderer/Opengl3_Renderer.h"

#include <glad/glad.h>

namespace ZM
{
	OGL3_Renderer::OGL3_Renderer(Settings s)
		:Renderer(s)
	{
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
	void *OGL3_Renderer::CreatMesh(OAA::Array<Vertex> verts, OAA::Array<unsigned int> indices)
	{
		// Vertex array, Vertex buffer, Elemnet buffer
		unsigned int *buffers = new unsigned int[3];
		
		//Vertex Array
		glGenVertexArrays(1, buffers);
		glBindVertexArray(buffers[0]);

		// vertex buffer object
		glGenBuffers(1, &buffers[1]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*verts.Length(), &verts[0], GL_STATIC_DRAW);
	    
		//Vertex Elements buffer
		glGenBuffers(1, &buffers[2]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.Length(), &indices[0], GL_STATIC_DRAW);
		
		// vertex positions
    	glEnableVertexAttribArray(0);	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Pos));
		// vertex positions
    	glEnableVertexAttribArray(1);	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Norm));
	   // vertex positions
    	glEnableVertexAttribArray(2);	
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

    	glBindVertexArray(0);
		
		return buffers;
	}
}
