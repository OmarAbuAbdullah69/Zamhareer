#pragma once

#include "windowing.hpp"
#include "event/event.hpp"

namespace zm {
  class core {
    public:
      static core &instance() {
        static core c;
        return c;
      }
#ifdef WINDOWED
      window_id creat_window(const char *name, unsigned width, unsigned height, window_id parent_window=0);
	  void update_window(window_id w=0);
	  void close_window(window_id w=0);
	  bool is_window_closed(window_id);

	  void set_window_size(window_id w, unsigned width, unsigned height);
	  void get_window_size(window_id w, unsigned &width, unsigned &height);

	  void set_window_pos(window_id w, unsigned posx, unsigned posy);
	  void get_window_pos(window_id w, unsigned &posx, unsigned &posy);
#endif
	  void attach_event(
#ifdef WINDOWED 
			  window_id w,
#endif
			  void (*event_callback)(const event &));
  };
}
