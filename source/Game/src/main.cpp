#include<ZM/Engine.h>
#include<ZM/window_impl/glfw_Window.h>
#include<vec2.hpp> 

#include <ZM/Event/MouseEvent.h>

#include "TestLayer.h"

int main()
{
	glm::vec2 vec(4.0, 234.2);
	ZM::Window win("test window", glm::vec2(640, 480));
	ZM::Engine en;
	en.PushBackLayer<LayerA>("layer a1");
	en.PushBackLayer<LayerA>("layer a2");
	en.SetViewPort(&win);
	en.Init();
	while (!en.ShouldClose()) {
		en.Update();
	}
	en.Terminate();
	return 0;
}
