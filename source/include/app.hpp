#pragma once
#include "zm/zm.hpp"
class app : public zm::engine {
public:
  app() {
    mSettings.vs.title = "test title";
    mRuning = true;
  }
  ~app() {}
  void init() override { zm::engine::init(); }
  void update() override { zm::engine::update(); }
  void render() override { zm::engine::render(); }
	void onEvent(zm::event e) override {
		zm::engine::onEvent(e);
		if (e.type == zm::eventType::KeyPressed){
			LOGINFO("key code: {%0}, mod {%1}", static_cast<int>(e.key.code), static_cast<int>(e.key.modifiers));
		}
	}

private:
};
