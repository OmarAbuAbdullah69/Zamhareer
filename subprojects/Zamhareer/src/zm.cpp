#include "zm/zm.hpp"
namespace zm {
engine *engine::sInstance = nullptr;
engine::engine() { sInstance = this; }
engine::~engine() {
  if (sInstance == this)
    sInstance = nullptr;
  if (mViewport) {
    delete mViewport;
  }
}
void engine::init() { mViewport = new viewport(mSettings.vs); }
void engine::update() {}
void engine::render() {
  mViewport->update();
  if (mViewport->shouldClose())
    mRuning = false;
}
void engine::onEvent(event e) {}
bool engine::isRuning() { return mRuning; }
} // namespace zm
