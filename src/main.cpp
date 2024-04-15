#include <ostream>
#include <zm.hpp>


int main (int argc, char *argv[]) {

    zm::core &c = zm::core::instance();
	zm::window_id window1 = c.creat_window("test window", 640, 480);

	c.set_window_pos(window1, 100, 100);

	while (!(c.is_window_closed(window1))) {
		c.update_window();
		unsigned width, height, posx, posy;
		c.get_window_size(window1, width, height);
		c.get_window_pos(window1, posx, posy);
		
		std::cout << "window size: " << width << ' ' << height << std::endl 
			<< "window pos: " << posx << ' ' << posy << std::endl;
	}
	c.close_window();
    return 0;
}
