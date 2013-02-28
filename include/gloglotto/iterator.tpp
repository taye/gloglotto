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

#include <gloglotto/iterator>

namespace gloglotto
{
	namespace iterator
	{
		template <typename Class, typename Constant>
		accessible<Class, Constant>::accessible (Class* object, int current)
		{
			_object  = object;
			_current = current;
		}

		template <typename Class, typename Constant>
		accessible<Class, Constant>::accessible (accessible<Class, Constant> const& from)
		{
			_object  = from._object;
			_current = from._current;
		}

		template <typename Class, typename Constant>
		typename accessible<Class, Constant>::reference
		accessible<Class, Constant>::operator * (void) const
		{
			return (*_object)[_current];
		}

		template <typename Class, typename Constant>
		typename accessible<Class, Constant>::reference
		accessible<Class, Constant>::operator [] (int n) const
		{
			return (*_object)[n];
		}

		template <typename Class, typename Constant>
		typename accessible<Class, Constant>::pointer
		accessible<Class, Constant>::operator -> (void) const
		{
			return &(*_object)[_current];
		}

		template <typename Class, typename Constant>
		accessible<Class, Constant>&
		accessible<Class, Constant>::operator ++ (void)
		{
			if (_current == -1) {
				return *this;
			}

			if (++_current >= size) {
				_current = -1;
			}

			return *this;
		}

		template <typename Class, typename Constant>
		accessible<Class, Constant>
		accessible<Class, Constant>::operator ++ (int)
		{
			if (_current == -1) {
				return *this;
			}

			accessible<Class, Constant> result(this);
			{
				if (++_current >= size) {
					_current = -1;
				}
			}
			return result;
		}

		template <typename Class, typename Constant>
		accessible<Class, Constant>&
		accessible<Class, Constant>::operator -- (void)
		{
			if (_current == -1) {
				_current = size - 1;

				return *this;
			}

			_current--;

			return *this;
		}

		template <typename Class, typename Constant>
		accessible<Class, Constant>
		accessible<Class, Constant>::operator -- (int)
		{
			accessible<Class, Constant> result(this);
			{
				if (_current == -1) {
					_current = size - 1;
				}
				else {
					_current--;
				}
			}
			return result;
		}

		template <typename Class, typename Constant>
		accessible<Class, Constant>
		accessible<Class, Constant>::operator + (int n) const
		{
			int current = _current + n;

			if (current >= size || current < 0) {
				return accessible<Class, Constant>(_object, -1);
			}
			else {
				return accessible<Class, Constant>(_object, current);
			}
		}

		template <typename Class, typename Constant>
		accessible<Class, Constant>&
		accessible<Class, Constant>::operator += (int n)
		{
			int current = _current + n;

			if (current >= size || current < 0) {
				_current = -1;
			}
			else {
				_current = current;
			}
		}

		template <typename Class, typename Constant>
		accessible<Class, Constant>
		accessible<Class, Constant>::operator - (int n) const
		{
			int current = _current - n;

			if (current >= size || current < 0) {
				return accessible<Class, Constant>(_object, -1);
			}
			else {
				return accessible<Class, Constant>(_object, current);
			}
		}

		template <typename Class, typename Constant>
		accessible<Class, Constant>&
		accessible<Class, Constant>::operator -= (int n)
		{
			int current = _current - n;

			if (current >= size || current < 0) {
				_current = -1;
			}
			else {
				_current = current;
			}
		}

		template <typename Class, typename Constant>
		bool
		accessible<Class, Constant>::operator == (accessible<Class, Constant> const& other) const
		{
			return _object == other._object && _current == other._current;
		}

		template <typename Class, typename Constant>
		bool
		accessible<Class, Constant>::operator != (accessible<Class, Constant> const& other) const
		{
			return _object != other._object || _current != other._current;
		}

		template <typename Class, typename Constant>
		bool
		accessible<Class, Constant>::operator > (accessible<Class, Constant> const& other) const
		{
			return _object == other._object && _current > other._current;
		}

		template <typename Class, typename Constant>
		bool
		accessible<Class, Constant>::operator >= (accessible<Class, Constant> const& other) const
		{
			return _object == other._object && _current >= other._current;
		}

		template <typename Class, typename Constant>
		bool
		accessible<Class, Constant>::operator < (accessible<Class, Constant> const& other) const
		{
			return _object == other._object && _current < other._current;
		}

		template <typename Class, typename Constant>
		bool
		accessible<Class, Constant>::operator <= (accessible<Class, Constant> const& other) const
		{
			return _object == other._object && _current <= other._current;
		}
	}
}
