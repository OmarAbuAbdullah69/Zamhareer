#pragma once

#include "zm/zm.hpp"
#include <iostream>
class app: public zm::engine {
	public:
		app() {
			std::cout << "app was created\n";
		}
		void init() override {
			zm::engine::init();
			std::cout << "app init\n";
			
		}
		void update() override {
			zm::engine::update();
		}
		void render() override {
			zm::engine::render();
		}
};
