/** Copyleft (ɔ) meh. - http://meh.schizofreni.co
 *
 * This file is part of gloglotto - https://github.com/meh/gloglotto
 *
 * gloglotto is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gloglotto is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gloglotto. If not, see <http://www.gnu.org/licenses/>.
 */

#include <gloglotto/window>

namespace gloglotto
{
	namespace window
	{
		void
		create (int* argc, char* argv[], size size, std::string name) throw (exception)
		{
			glutInit(argc, argv);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

			glutInitWindowSize(size.width, size.height);

			glutCreateWindow(name.c_str());

			unsigned err = glewInit();
			if (err != GLEW_OK) {
				throw exception(reinterpret_cast<const char*>(glewGetErrorString(err)));
			}
		}

		void
		create (int* argc, char* argv[], size size, position position, std::string name) throw (exception)
		{
			glutInit(argc, argv);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

			glutInitWindowSize(size.width, size.height);
			glutInitWindowPosition(position.x, position.y);

			glutCreateWindow(name.c_str());

			unsigned err = glewInit();
			if (err != GLEW_OK) {
				throw exception(reinterpret_cast<const char*>(glewGetErrorString(err)));
			}
		}

		void
		loop (void)
		{
			glutMainLoop();
		}

		void
		loop (std::function<void(void)> before)
		{
			before();
			loop();
		}

		void
		loop (std::function<void(void)> before, std::function<void(void)> after)
		{
			loop(before);
			after();
		}

		void
		exit (void)
		{
			std::exit(0);
		}

		void
		render (void)
		{
			glutSwapBuffers();
		}

		void
		update (void)
		{
			glutPostRedisplay();
		}

		namespace callbacks
		{
			std::map<int, void*>        closures;
			std::map<int, class timer*> timers;

			template <typename Signature, typename ...Args>
			static inline
			void
			closure (int type, Args... args) throw (std::invalid_argument)
			{
				if (closures.find(type) == closures.end()) {
					throw std::invalid_argument("unknown callback");
				}

				(*static_cast<std::function<Signature>*>(closures[type]))(args...);
			}

			void
			resize (int width, int height)
			{
				closure<void(int, int)>(event::resize, width, height);
			}

			void
			render (void)
			{
				closure<void(void)>(event::render);
			}

			void
			idle (void)
			{
				closure<void(void)>(event::idle);
			}

			void
			visible (int state)
			{
				closure<void(bool)>(event::visible, state == GLUT_VISIBLE);
			}

			void
			keyboard (unsigned char ch, int x, int y)
			{
				closure<void(key, int, int)>(event::keyboard, key(ch, glutGetModifiers()), x, y);
			}

			void
			keyboard_up (unsigned char ch, int x, int y)
			{
				closure<void(key, int, int)>(event::keyboard, key(ch, glutGetModifiers(), true), x, y);
			}

			void
			special (int ch, int x, int y)
			{
				closure<void(key, int, int)>(event::keyboard, key(ch, glutGetModifiers()), x, y);
			}

			void
			special_up (int ch, int x, int y)
			{
				closure<void(key, int, int)>(event::keyboard, key(ch, glutGetModifiers(), true), x, y);
			}

			static mouse mouse_current;

			void
			mouse_click (int button, int state, int x, int y)
			{
				if (state == GLUT_DOWN) {
					mouse_current._button    = mouse::cast(button);
					mouse_current._modifiers = glutGetModifiers();
					mouse_current._released  = false;

					closure<void(mouse, int, int)>(event::mouse::click, mouse_current, x, y);
				}
				else {
					mouse_current._released = true;

					closure<void(mouse, int, int)>(event::mouse::click, mouse_current, x, y);

					mouse_current._button    = mouse::cast(0);
					mouse_current._modifiers = 0;
				}
			}

			void
			mouse_motion (int x, int y)
			{
				closure<void(mouse, int, int)>(event::mouse::motion, mouse_current, x, y);
			}

			void
			mouse_motion_passive (int x, int y)
			{
				closure<void(mouse, int, int)>(event::mouse::motion, mouse(), x, y);
			}

			void
			timer (int id)
			{
				auto iterator = timers.find(id);
				if (iterator == timers.end()) {
					return;
				}

				auto timer = iterator->second;
				if (!timer->stopped()) {
					timer->call();
				}

				if (timer->repeat() && !timer->stopped()) {
					glutTimerFunc(timer->after().count(), callbacks::timer, timer->id());
				}
				else {
					timers.erase(iterator);
					delete timer;
				}
			}
		}

		bool
		key::known (int special)
		{
			switch (special) {
				case F1:
				case F2:
				case F3:
				case F4:
				case F5:
				case F6:
				case F7:
				case F8:
				case F9:
				case F10:
				case F11:
				case F12:

				case left:
				case right:
				case up:
				case down:

				case page_up:
				case page_down:
				case home:
				case end:
				case insert:
					return true;

				default:
					return false;
			}
		}

		key::key (int modifiers, bool released)
		{
			_key       = none << 16;
			_modifiers = modifiers;
			_released  = released;
		}

		key::key (unsigned char key, int modifiers, bool released)
		{
			if (key >= 1 && key <= 26 && key != tab && key != enter && key != backspace) {
				_key = key + 96;
			}
			else {
				_key = std::tolower(key);
			}

			_modifiers = modifiers;
			_released  = released;
		}

		key::key (char dumb, int modifiers, bool released)
		{
			unsigned char key = dumb;

			if (key >= 1 && key <= 26 && key != tab && key != enter && key != backspace) {
				_key = key + 96;
			}
			else {
				_key = std::tolower(key);
			}

			_modifiers = modifiers;
			_released  = released;
		}

		key::key (int key, int modifiers, bool released)
		{
			_key       = (known(key) ? key : none) << 16;
			_modifiers = modifiers;
			_released  = released;
		}

		key::key (key const& from)
		{
			_key       = from._key;
			_modifiers = from._modifiers;
			_released  = from._released;
		}

		bool
		key::operator == (unsigned char other)
		{
			return _key == std::tolower(other);
		}

		bool
		key::operator == (char other)
		{
			return _key == std::tolower((unsigned char) other);
		}

		bool
		key::operator == (int other)
		{
			if (known(other)) {
				return _key == (other << 16);
			}
			else {
				return _key == (none << 16);
			}
		}

		bool
		key::operator == (key const& other)
		{
			return _key == other._key && _modifiers == other._modifiers && _released == other._released;
		}

		bool
		key::operator != (unsigned char other)
		{
			return _key != std::tolower(other);
		}

		bool
		key::operator != (char other)
		{
			return _key != std::tolower((unsigned char) other);
		}

		bool
		key::operator != (int other)
		{
			if (known(other)) {
				return _key != (other << 16);
			}
			else {
				return _key != (none << 16);
			}
		}

		bool
		key::operator != (key const& other)
		{
			return _key != other._key || _modifiers != other._modifiers || _released != other._released;
		}

		bool
		key::special (void)
		{
			return (_key & 0xff) == 0;
		}

		unsigned char
		key::ch (void) throw (std::logic_error)
		{
			if (special()) {
				throw std::logic_error("this is a special key");
			}

			return _key & 0xff;
		}

		std::string
		key::name (void)
		{
			if (special()) {
				switch (_key >> 16) {
					case F1:  return "F1";
					case F2:  return "F2";
					case F3:  return "F3";
					case F4:  return "F4";
					case F5:  return "F5";
					case F6:  return "F6";
					case F7:  return "F7";
					case F8:  return "F8";
					case F9:  return "F9";
					case F10: return "F10";
					case F11: return "F11";
					case F12: return "F12";

					case left:  return "Left";
					case right: return "Right";
					case up:    return "Up";
					case down:  return "Down";

					case page_up:   return "PageUp";
					case page_down: return "PageDown";
					case home:      return "Home";
					case end:       return "End";
					case insert:    return "Insert";

					case none: return "None";
				}
			}
			else {
				switch (ch()) {
					case esc:       return "Esc";
					case space:     return "Space";
					case tab:       return "Tab";
					case enter:     return "Enter";
					case backspace: return "Backspace";
					case cancel:    return "Cancel";

					default: return std::string(1, ch());
				}
			}

			throw std::logic_error("unreachable");
		}

		bool
		key::alt (void)
		{
			return _modifiers & GLUT_ACTIVE_ALT;
		}

		bool
		key::shift (void)
		{
			return _modifiers & GLUT_ACTIVE_SHIFT;
		}

		bool
		key::ctrl (void)
		{
			return _modifiers & GLUT_ACTIVE_CTRL;
		}

		bool
		key::released (void)
		{
			return _released;
		}

		mouse::button
		mouse::cast (int value)
		{
			switch (value) {
				case GLUT_LEFT_BUTTON:
					return button::left;

				case GLUT_MIDDLE_BUTTON:
					return button::middle;

				case GLUT_RIGHT_BUTTON:
					return button::right;
			}

			return button::none;
		}

		mouse::mouse (int modifiers, bool released)
		{
			_button    = button::none;
			_modifiers = modifiers;
			_released  = released;
		}

		mouse::mouse (int button, int modifiers, bool released)
		{
			_button    = cast(button);
			_modifiers = modifiers;
			_released  = released;
		}

		mouse::mouse (mouse const& from)
		{
			*this = from;
		}

		bool
		mouse::alt (void)
		{
			return _modifiers & GLUT_ACTIVE_ALT;
		}

		bool
		mouse::shift (void)
		{
			return _modifiers & GLUT_ACTIVE_SHIFT;
		}

		bool
		mouse::ctrl (void)
		{
			return _modifiers & GLUT_ACTIVE_CTRL;
		}

		bool
		mouse::released (void)
		{
			return _released;
		}

		int
		timer::id (void)
		{
			return _id;
		}

		bool
		timer::repeat (void)
		{
			return _repeat;
		}

		void
		timer::stop (void)
		{
			_stopped = true;
		}

		bool
		timer::stopped (void)
		{
			return _stopped;
		}

		std::chrono::milliseconds
		timer::after (void)
		{
			return _after;
		}

		void
		timer::call (void)
		{
			_function(*this);
		}
	}
}
