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

#include <gloglotto/utility>
#include <gloglotto/window>

#include <map>

namespace gloglotto
{
	namespace window
	{
		namespace callbacks
		{
			extern std::map<int, void*>        closures;
			extern std::map<int, class timer*> timers;
		}

		template <class Duration>
		timer::timer (Duration duration, std::function<void(timer&)> function, bool repeat)
		{
			static int _last_id = 0;

			_id       = _last_id++;
			_function = function;

			after(duration);
			
			_repeat  = repeat;
			_stopped = false;
		}

		template <class Duration>
		void
		timer::after (Duration duration)
		{
			_after = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
		}

		template<int Callback, typename Function>
		void
		on (Function function) throw (std::invalid_argument, std::bad_typeid)
		{
			switch (Callback) {
				case event::resize: signature_assert<void(int, int)>(function);
					glutReshapeFunc(callbacks::resize);
					break;

				case event::render: signature_assert<void(void)>(function);
					glutDisplayFunc(callbacks::render);
					break;

				case event::idle: signature_assert<void(void)>(function);
					glutIdleFunc(callbacks::idle);
					break;

				case event::visible: signature_assert<void(bool)>(function);
					glutVisibilityFunc(callbacks::visible);
					break;

				case event::keyboard: signature_assert<void(key&, int, int)>(function);
					glutKeyboardFunc(callbacks::keyboard);
					glutKeyboardUpFunc(callbacks::keyboard_up);
					glutSpecialFunc(callbacks::special);
					glutSpecialUpFunc(callbacks::special_up);
					break;

				case event::mouse::click:  signature_assert<void(mouse&, int, int)>(function);
					glutMouseFunc(callbacks::mouse_click);
					break;

				case event::mouse::motion: signature_assert<void(mouse&, int, int)>(function);
					glutMotionFunc(callbacks::mouse_motion);
					glutPassiveMotionFunc(callbacks::mouse_motion_passive);
					break;

				default:
					throw std::invalid_argument("unknown callback");
			}

			if (callbacks::closures.find(Callback) != callbacks::closures.end()) {
				throw std::invalid_argument("the callback already exists");
			}

			callbacks::closures[Callback] = new decltype(to_function(function))(function);
		}

		template <class Duration>
		void
		after (Duration duration, std::function<void(timer&)> function)
		{
			timer* time = new timer(duration, function);

			callbacks::timers[time->id()] = time;

			glutTimerFunc(time->after().count(), callbacks::timer, time->id());
		}

		template <class Duration>
		void
		every (Duration duration, std::function<void(timer&)> function)
		{
			timer* time = new timer(duration, function, true);

			callbacks::timers[time->id()] = time;

			glutTimerFunc(time->after().count(), callbacks::timer, time->id());
		}
	}
}
