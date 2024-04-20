#include <ostream>
#include <zm.hpp>


int main (int argc, char *argv[]) {

    zm::core &c = zm::core::instance();
	zm::window_id window1 = c.creat_window("test window", 640, 480);
	c.attach_event(window1, [](const zm::event &e){
			e.log();
			});

	while (!(c.is_window_closed(window1))) {
		c.update_window(window1);
	}
	c.close_window();
    return 0;
}
