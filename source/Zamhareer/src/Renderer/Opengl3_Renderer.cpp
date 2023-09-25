#include "ZM/Renderer/Opengl3_Renderer.h"

#include <glad/glad.h>
#include <iostream>
#include "ZM/oaa_String.h"

namespace ZM
{

	Texture::Texture()
	{

	}
	Texture::Texture(Image i)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		if (i.Data) {
			if(i.NRC == 3){
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, i.Width, i.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, i.Data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else if (i.NRC == 4) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.Width, i.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, i.Data);
				glGenerateMipmap(GL_TEXTURE_2D);
				
			}
		}
		else {
			std::cout << "Loading Texture Error: Empty image" << std::endl;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture::Use()
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	static unsigned int MakeShader(const char *path)
	{
		unsigned int ID;

		OAA::String _path(path);
		int verterr, fragerr;
		reload:
		OAA::String vertex_src = OAA::LoadFile((_path+"/vertex.glsl").cstr(), &verterr);
		OAA::String fragment_src = OAA::LoadFile((_path+"/fragment.glsl").cstr(), &fragerr);


		if(verterr || fragerr)
		{
			_path = "resources/shaders/default";
			goto reload;
		}
		
		const char *vsrc = vertex_src.cstr();
		const char *fsrc = fragment_src.cstr();
	
		// 2. compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
			
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vsrc, NULL);

		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			_path = "resources/shaders/default";
			goto reload;
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fsrc, NULL);

		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			_path = "resources/shaders/default";
			goto reload;
		}

		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		// print linking errors if any
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			_path = "resources/shaders/default";
			goto reload;
		}	  
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return ID;
	}
	OGL3_Renderer::OGL3_Renderer(Settings s)
		:Renderer(s)
	{
	}
	void OGL3_Renderer::Init()
	{
		ResetSettings();
		if(m_Settings.GammaCorrection)
			glEnable(GL_FRAMEBUFFER_SRGB); 
	}
	void OGL3_Renderer::Terminate()
	{

	}
	void *OGL3_Renderer::CreatMesh(OAA::Array<Vertex> &verts, OAA::Array<unsigned int> &indices, const Material &mat)
	{
		// Vertex array, Vertex buffer, Elemnet buffer
		MeshData *md = new MeshData;
		md->ShaderProgram = MakeShader("resources/shaders/default");
		md->Count = indices.Length();
		

		int TexturesCount = sizeof(Material)/sizeof(Image);
		Texture *Textures = new Texture[TexturesCount];
		md->TexturesCount = TexturesCount;
		md->Textures = Textures;
		Textures[0] = Texture(mat.Albedo);

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
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Pos));
		// vertex positions
    	glEnableVertexAttribArray(1);	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Norm));
	   // vertex positions
    	glEnableVertexAttribArray(2);	
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

    	glBindVertexArray(0);
		
		return md;
	}
	void OGL3_Renderer::DrawMesh(void *data,  glm::mat4 transform, glm::mat4 viewprojection)
	{
		MeshData _data = *((MeshData *)data);
		glBindVertexArray(_data.VAO);
		glUseProgram(_data.ShaderProgram);

		int VPSLoc = glGetUniformLocation(_data.ShaderProgram, "ViewportSize");
		if(!(VPSLoc == -1))
		{
			glUniform2f(VPSLoc, m_Settings.RenderSize.x, m_Settings.RenderSize.y);
		}

		int TranLoc = glGetUniformLocation(_data.ShaderProgram, "Transform");
		if(!(TranLoc == -1))
		{
			glUniformMatrix4fv(TranLoc, 1, GL_FALSE, &transform[0][0]);
		}
	
		int VPLoc = glGetUniformLocation(_data.ShaderProgram, "ViewProjection");
		if(!(VPLoc == -1))
		{
			glUniformMatrix4fv(VPLoc, 1, GL_FALSE, &viewprojection[0][0]);
		}	
		for(unsigned int i=0; i<_data.TexturesCount; i++)
		{
			_data.Textures[i].Use();
		}
		glDrawElements(GL_TRIANGLES, _data.Count, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	void OGL3_Renderer::ResetSettings()
	{
		// viewport
		unsigned x, y, w, h;
		x = m_Settings.RenderPos.x;
		y = m_Settings.RenderPos.y;
		w = m_Settings.RenderSize.x;
		h = m_Settings.RenderSize.y;
		glViewport(x, y, w, h);
	}
}
