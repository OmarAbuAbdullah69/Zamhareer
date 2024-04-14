#include "core.hpp"

namespace zm {

	std::vector<window> window::s_windows;

#ifdef WINDOWED
	window_id core::creat_window(const char * name, unsigned width, unsigned height, window_id parent_window) {
		return window::s_creat_window(name, width, height, parent_window);
	}
	void core::update_window(window_id w) {
		if(!w) {
			for(window &win : window::s_windows) {
				win.update();
			}
		} else {
			window::s_windows.at(w-1).update();
		}
	}
	void core::close_window(window_id w) {
		if(!w) {
			for(window &win : window::s_windows) {
				win.close();
			}
		} else {
			window::s_windows.at(w-1).update();
		}
	}
	bool core::is_window_closed(window_id w) {
		return !window::s_windows.at(w-1).m_opened;
	}
#endif

}
