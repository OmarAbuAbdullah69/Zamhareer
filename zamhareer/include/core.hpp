#pragma once

namespace zm {
  class core {
    public:
      static core &instance() {
        static core c;
        return c;
      }
      void sayhey();
  };
}
