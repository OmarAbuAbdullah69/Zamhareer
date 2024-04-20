#pragma once

#include <vector>
#ifdef DEB_BUILD
#include <iostream>
#endif // DEBUG

namespace zm {
	enum class event_type{
		none= 0,
		//window
		window_resize, window_repos,
		//key board
		key_press, key_down, key_release,
		// mouse
		mouse_move, mouse_button_press, mouse_button_release,
		mouse_scroll
	};

	class event {
		friend class event_stack;
		public:
			virtual event_type get_type() const = 0;
			inline bool is_handled() const {
				return m_handled;
			}
#ifdef DEB_BUILD
			virtual void log() const = 0;
#endif // DEBUG
		private:
			bool m_handled = false;
	};

}
