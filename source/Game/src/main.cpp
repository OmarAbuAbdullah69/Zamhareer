#include<ZM/Engine.h>
#include<ZM/window_impl/glfw_Window.h>
#include<vec2.hpp> 

#include <ZM/Event/MouseEvent.h>

int main()
{
	glm::vec2 vec(4.0, 234.2);
	ZM::Window win("test window", glm::vec2(640, 480));
	ZM::Engine en;
	en.SetViewPort(&win);
	en.Init();
	while (!en.ShouldClose()) {
		en.Update();
	}
	en.Terminate();
	return 0;
}
