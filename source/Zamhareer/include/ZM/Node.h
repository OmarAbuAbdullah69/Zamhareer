#pragma once

#include "oaa_String.h"
#include "Event/Event.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "oaa_Array.h"

namespace ZM
{
	class Node
	{
		public:
			Node(const char *name, Node *parent = NULL)
				:m_Name(name), m_Parent(parent)
			{
				if(m_Parent)
				{
					m_Parent->AddChild(this);
				}
			}
			virtual void Init()
			{
				for(Node *n : m_Childrens)
				{
					n->Init();
				}
			}
			virtual void Update(double delta)
			{
				for(Node *n : m_Childrens)
				{
					n->Update(delta);
				}
			}
			virtual void OnEvent(Event &event)
			{
				for(size_t i=m_Childrens.Length(); i >= 0; i--)
				{
					m_Childrens[i]->OnEvent(event);
				}
			}
			inline OAA::String GetName() const {return m_Name;}
			inline Node *GetParent(){return m_Parent;}
			inline void AddChild(Node *node){m_Childrens.PushBack(node);}
		protected:
			OAA::String m_Name;
			Node *m_Parent;
			OAA::Array<Node *> m_Childrens;
	};
	class Node2D: public Node
	{
		public:
			Node2D(const char * name, Node *parent);
			virtual void Init() override;
			virtual void Update(double delta) override;
			virtual void OnEvent(Event &event) override;
			void Translate(glm::vec2 to);
			void Scale(glm::vec2 by);
			void Rotate(float by);
			glm::mat4 GetTransform();
		protected:
			glm::vec2 m_Translation = glm::vec2(0.0); 
			glm::vec2 m_Scale = glm::vec2(1.0);
			float m_Rotation = 0;
	};
}
