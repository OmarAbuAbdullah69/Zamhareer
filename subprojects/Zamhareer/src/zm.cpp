#include "zm/zm.hpp"
namespace zm {
	engine *engine::sInstance = nullptr;
	engine::engine() {
		sInstance = this;
	}
	engine::~engine() {
		if (sInstance == this)
			sInstance = nullptr;
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
		if (mViewport->shouldClose())
			mRuning = false;
	}
	void oneEvent(event e) {
	}
	bool engine::isRuning() {
		return mRuning;
	}
}
