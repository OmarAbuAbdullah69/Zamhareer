#pragma once
#include "Node.h"
namespace ZM
{
	class Camera2D :public Node2D
	{
		public:
			Camera2D(const char *name, Node2D *parent, float l ,float r, float b, float t);
			virtual void Init() override;
			virtual void Update(double delta) override;
			virtual void OnEvent(Event &e) override;
			glm::mat4 GetView();
		private:
			float left, right, bottom, top;
			float nearPlane = -1.0f;
			float farPlane = 1.0f;
	};
}
