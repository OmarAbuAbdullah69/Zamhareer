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
	void *OGL3_Renderer::CreatMesh(OAA::Array<Vertex> &verts, OAA::Array<unsigned int> &indices)
	{
		// Vertex array, Vertex buffer, Elemnet buffer
		MeshData *md = new MeshData;
		
		md->count = indices.Length();

		//Vertex Array
		glGenVertexArrays(1, &(md->VAO));
		glBindVertexArray((md->VAO));

		// vertex buffer object
		glGenBuffers(1, &(md->VBO));
		glBindBuffer(GL_ARRAY_BUFFER, md->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*verts.Length(), &verts[0], GL_STATIC_DRAW);
	    
		//Vertex Elements buffer
		glGenBuffers(1, &(md->EBO));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, md->EBO);
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
		
		return md;
	}
	void OGL3_Renderer::DrawMesh(void *data)
	{
		MeshData _data = *((MeshData *)data);
		glBindVertexArray(_data.VAO);
		glDrawElements(GL_TRIANGLES, _data.count, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
