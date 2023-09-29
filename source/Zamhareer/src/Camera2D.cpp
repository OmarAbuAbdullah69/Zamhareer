#include "ZM/Camera2D.h"

namespace ZM
{
	Camera2D::Camera2D(const char *name, Node2D *parent, float l ,float r, float b, float t)
		:Node2D(name, parent), left(l), right(r), bottom(b), top(t)
	{
		
	}
	void Camera2D::Init()
	{

	}
	void Camera2D::Update(double delta)
	{

	}
	void Camera2D::OnEvent(Event &event)
	{

	}
	glm::mat4 Camera2D::GetView()
	{
		return glm::inverse(GetTransform()) * glm::ortho(left, right, bottom, top, nearPlane, farPlane);
	}
}
