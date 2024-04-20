#pragma once

#include "event.hpp"

namespace zm {
	class window_resize_event: public event {
		friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::window_resize;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "window resize event : "<< m_width << ' ' << m_height << std::endl;
			}
		#endif // DEBUG
			inline unsigned get_width() const {
				return m_width;
			}
			inline unsigned get_height() const {
				return m_height;
			}
		private:
			window_resize_event(unsigned width, unsigned height) 
				:m_width(width), m_height(height){}

			// later replace with vec2
			unsigned m_width, m_height;
	};
	class window_repos_event: public event {
		friend class window;
		public:
			virtual event_type get_type() const override {
				return event_type::window_repos;
			}
		#ifdef DEB_BUILD
			virtual void log() const override {
				std::cout << "window repos event : "<< m_posx << ' ' << m_posy << std::endl;
			}
		#endif // DEBUG
			inline unsigned get_posx() const {
				return m_posx;
			}
			inline unsigned get_posy() const {
				return m_posy;
			}
		private:
			window_repos_event(unsigned posx, unsigned posy) 
				:m_posx(posx), m_posy(posy){}

			// later replace with vec2
			unsigned m_posx, m_posy;
	};
}
