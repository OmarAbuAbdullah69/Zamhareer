#pragma once

#define ZM_MAIN(APP) \
	int main (int argc, char *argv[]) {\
		APP a;\
		a.init();\
		while(a.isRuning()) {\
			a.update();\
		}\
		return 0;\
	}


namespace zm {
	class engine {

		protected:
			engine();

		public:
			~engine();
			static engine &instance() {
				return *sInstance;
			}

			virtual void init();
			virtual void update();
			virtual void render();
			
			bool isRuning();
	
		private:
			static engine *sInstance;
			bool mRuning=false;
	};
}
