#include <zm.hpp>


int main (int argc, char *argv[]) {

    zm::core &c = zm::core::instance();
	zm::window_id window = c.creat_window("test window", 640, 480);
	while (true) {
		c.update_window();
	}
	c.close_window();
    return 0;
}
