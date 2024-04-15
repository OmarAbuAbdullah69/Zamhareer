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
	
	void core::set_window_size(window_id w, unsigned width, unsigned height) {
		if(!w)
			throw std::runtime_error("invaled window_id\n");
		window::s_windows.at(w-1).set_size(width, height);
	}
	void core::get_window_size(window_id w, unsigned &width, unsigned &height) {
		if(!w)
			throw std::runtime_error("invaled window_id\n");
		window::s_windows.at(w-1).get_size(width, height);
	}

	void core::set_window_pos(window_id w, unsigned posx, unsigned posy) {
		if(!w)
			throw std::runtime_error("invaled window_id\n");
		window::s_windows.at(w-1).set_pos(posx, posy);
	}
	void core::get_window_pos(window_id w, unsigned &posx, unsigned &posy) {
		if(!w)
			throw std::runtime_error("invaled window_id\n");
		window::s_windows.at(w-1).get_pos(posx, posy);
	}

#endif

}
