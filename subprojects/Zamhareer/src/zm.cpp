#include "zm/zm.hpp"
namespace zm {
	engine::engine() {
	}
	engine::~engine() {
		if(mViewport) {
			delete mViewport;
		}
	}
	void engine::init() {
		mViewport = new viewport(mSettings.title.c_str(),
				mSettings.viewportWidth,
				mSettings.viewportHeight);
	}
	void engine::update() {
	}
	void engine::render() {
		mViewport->update();
	}
	bool engine::isRuning() {
		return mRuning;
	}
}
