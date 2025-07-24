#pragma once

#include "zm/viewport/viewport.hpp"
#define ZM_MAIN(APP) \
	int main (int argc, char *argv[]) {\
		APP a;\
		a.init();\
		while(a.isRuning()) {\
			a.update();\
			a.render();\
		}\
		return 0;\
	}

namespace zm {

	struct settings {
		std::string title;
		int viewportWidth = 640;
		int viewportHeight = 480;
	};

	class engine {

		protected:
			engine();
			settings mSettings;

		public:
			~engine();
			static engine &instance() {
				return *sInstance;
			}

			virtual void init();
			virtual void update();
			virtual void render();
			
			bool isRuning();

		protected:
			bool mRuning=false;

		private:
			static engine *sInstance;
			viewport *mViewport;
	};
}
