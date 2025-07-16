#include "zm/zm.hpp"
#include <iostream>
namespace zm {
	engine::engine() {
		std::cout << "engine was created\n";
	}
	engine::~engine() {

	}
	void engine::init() {
		std::cout << "engine was init\n";
	}
	void engine::update() {

	}
	void engine::render() {

	}
	bool engine::isRuning() {
		return mRuning;
	}
}
