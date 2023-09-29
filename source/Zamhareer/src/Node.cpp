#include "ZM/Node.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ZM
{
	Node2D::Node2D(const char *name, Node2D *parent)
		:Node(name, parent)
	{
		
	}
	void Node2D::Init()
	{
		Node::Init();
	}
	void Node2D::Update(double delta)
	{
		Node::Update(delta);
	}
	void Node2D::OnEvent(Event &event)
	{
		Node::OnEvent(event);
	}
	void Node2D::Translate(glm::vec2 to)
	{
		m_Translation += to;
	}
	void Node2D::Scale(glm::vec2 by)
	{
		m_Scale *= by;
	}
	void Node2D::Rotate(float by)
	{
		m_Rotation += by;
	}
	glm::mat4 Node2D::GetTransform()
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.0), glm::vec3(m_Translation.x, m_Translation.y, 0.0));
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0), m_Rotation, glm::vec3(0.0, 0.0, -1.0));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(m_Scale.x, m_Scale.y, 1.0));
		if(m_Parent)
		{	
			return translation*scale*rotation*((Node2D *)m_Parent)->GetTransform();
		}
		return translation*rotation*scale;
	}
}
