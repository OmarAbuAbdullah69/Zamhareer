#pragma once

#include "key_event.hpp"

namespace zm {
	class key_press_event: public key_event{
		friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::key_press;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "mouse press button: " << get_key() << " mod: " << get_mod() << std::endl;
			}
		#endif // DEBUG
		private:
			key_press_event(int key, int mod)
				:key_event(key, mod) {}
	};
	class key_down_event: public key_event{
		friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::key_down;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "mouse press button: " << get_key() << " mod: " << get_mod() << std::endl;
			}
		#endif // DEBUG
		private:
			key_down_event(int key, int mod)
				:key_event(key, mod) {}
	};
	class key_release_event: public key_event {
		friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::key_release;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "mouse release button: " << get_key() << std::endl;
			}
		#endif // DEBUG
		private:
			key_release_event(int key, int mod)
				:key_event(key, mod) {}
	};

	class char_type_event: public event {
			friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::key_release;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "char type event: " << m_char << std::endl;
			}
		#endif // DEBUG
			char_type_event(int c)
				:m_char(c) {}
			inline int get_char() const { return m_char;}
		private:
			int m_char;
	};

}
