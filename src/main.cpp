#include <zm.hpp>


int main (int argc, char *argv[]) {

    zm::core &c = zm::core::instance();
	zm::window_id window1 = c.creat_window("test window", 640, 480);
	while (!(c.is_window_closed(window1))) {
		c.update_window();
	}
	c.close_window();
    return 0;
}
