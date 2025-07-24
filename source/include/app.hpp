#pragma once

#include "zm/zm.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
class app: public zm::engine {
	public:
		app() {
			mSettings.title = "test title";
			mRuning = true;
		}
		~app() {
		}
		void init() override {
			zm::engine::init();
			
		}
		void update() override {
			zm::engine::update();
		}
		void render() override {
			zm::engine::render();
		}
	private:
};
