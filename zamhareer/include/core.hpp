#pragma once

#include "windowing.hpp"


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
#endif
  };
}
