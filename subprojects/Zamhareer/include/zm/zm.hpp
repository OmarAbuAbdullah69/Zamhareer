#pragma once

#include "events.hpp"
#include "logger.hpp"

#include "zm/viewport/viewport.hpp"
#define ZM_MAIN(APP)                                                           \
  int main(int argc, char *argv[]) {                                           \
    APP a;                                                                     \
    a.init();                                                                  \
    while (a.isRuning()) {                                                     \
      a.update();                                                              \
      a.render();                                                              \
    }                                                                          \
    return 0;                                                                  \
  }

namespace zm {

struct settings {
  viewportSettings vs;
};

class engine {

protected:
  engine();
  settings mSettings;

public:
  virtual ~engine();
  engine(const engine &) = delete;
  engine &operator=(const engine &) = delete;
  static engine &inst() { return *sInstance; }

  virtual void init();
  virtual void update();
  virtual void render();
  virtual void onEvent(event);

  bool isRuning();

protected:
  bool mRuning = false;

private:
  static engine *sInstance;
  viewport *mViewport = nullptr;
};
} // namespace zm
