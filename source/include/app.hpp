#pragma once

#include "zm/zm.hpp"
#include <GLFW/glfw3.h>
class app : public zm::engine {
public:
  app() {
    mSettings.title = "test title";
		mSettings.viewportHeight = 20;
		mSettings.viewportWidth = 20;
    mRuning = true;
  }
  ~app() {}
  void init() override { zm::engine::init(); }
  void update() override { zm::engine::update(); }
  void render() override { zm::engine::render(); }

private:
};
