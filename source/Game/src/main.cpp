#include <ZM/Engine.h>

#include <ZM/Window/glfw_impl.h>
#include <ZM/Window/Window.h>
#include <ZM/Renderer/Opengl3_Renderer.h>

#include <vec2.hpp> 

#include <ZM/Event/MouseEvent.h>

#include "TestLayer.h"

#include <vec2.hpp>

int main()
{
	glm::vec2 vec(4.0, 234.2);
	ZM::Window<ZM::glfw_imple_window> win("test window", glm::vec2(640, 480));
	ZM::Engine en;
	ZM::Settings s = {
		.RenderSize = glm::vec2(640, 480),
		.RenderPos = glm::vec2(0, 0)
	};
	en.SetRenderer<ZM::OGL3_Renderer>(s);
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

