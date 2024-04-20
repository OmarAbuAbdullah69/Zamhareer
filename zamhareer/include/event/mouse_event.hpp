#pragma once

#include "event.hpp"
#include "key_event.hpp"

namespace zm {
	class mouse_move_event: public event {
		friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::mouse_move;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "mouse pos event : "<< m_posx << ' ' << m_posy << std::endl;
			}
		#endif // DEBUG
			inline float get_posx() const {
				return m_posx;
			}
			inline float get_posy() const {
				return m_posy;
			}
		private:
			float m_posx, m_posy;

			mouse_move_event(unsigned posx, unsigned posy) 
				: m_posx(posx), m_posy(posy){}
	};

	class mouse_scroll_event: public event {
		friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::mouse_scroll;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "mouse scroll event : "<< m_offsetx << ' ' << m_offsety << std::endl;
			}
		#endif // DEBUG
			inline float get_offsetx() const {
				return m_offsetx;
			}
			inline float get_offsety() const {
				return m_offsety;
			}
		private:
			mouse_scroll_event(float x, float y) 
				: m_offsetx(x), m_offsety(y) {}
			float m_offsetx, m_offsety;
	};

	class mouse_button_press_event: public key_event{
		friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::mouse_button_press;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "mouse press button: " << get_key() << " mod: " << get_mod() << std::endl;
			}
		#endif // DEBUG
		private:
			mouse_button_press_event(int key, int mod)
				:key_event(key, mod) {}
	};
	class mouse_button_release_event: public key_event {
		friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::mouse_button_release;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "mouse release button: " << get_key() << std::endl;
			}
		#endif // DEBUG
		private:
			mouse_button_release_event(int key, int mod)
				:key_event(key, mod) {}
	};
}
