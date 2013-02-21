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
		template <typename Class>
		accessible<Class>::accessible (Class* object, difference_type const& current)
		{
			_object  = object;
			_current = current;
		}

		template <typename Class>
		accessible<Class>::accessible (accessible<Class> const& from)
		{
			_object  = from._object;
			_current = from._current;
		}

		template <typename Class>
		typename accessible<Class>::reference
		accessible<Class>::operator * (void) const
		{
			return (*_object)[_current];
		}

		template <typename Class>
		typename accessible<Class>::reference
		accessible<Class>::operator [] (difference_type const& n) const
		{
			return (*_object)[n];
		}

		template <typename Class>
		typename accessible<Class>::pointer
		accessible<Class>::operator -> (void) const
		{
			return &(*_object)[_current];
		}

		template <typename Class>
		accessible<Class>&
		accessible<Class>::operator ++ (void)
		{
			if (_current == -1) {
				return *this;
			}

			if (++_current >= size) {
				_current = -1;
			}

			return *this;
		}

		template <typename Class>
		accessible<Class>
		accessible<Class>::operator ++ (int)
		{
			if (_current == -1) {
				return *this;
			}

			accessible<Class> result(this);
			{
				if (++_current >= size) {
					_current = -1;
				}
			}
			return result;
		}

		template <typename Class>
		accessible<Class>&
		accessible<Class>::operator -- (void)
		{
			if (_current == -1) {
				_current = size - 1;

				return *this;
			}

			_current--;

			return *this;
		}

		template <typename Class>
		accessible<Class>
		accessible<Class>::operator -- (int)
		{
			accessible<Class> result(this);
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

		template <typename Class>
		accessible<Class>
		accessible<Class>::operator + (difference_type const& n) const
		{
			difference_type current = _current + n;

			if (current >= size || current < 0) {
				return accessible<Class>(_object, -1);
			}
			else {
				return accessible<Class>(_object, current);
			}
		}

		template <typename Class>
		accessible<Class>&
		accessible<Class>::operator += (difference_type const& n)
		{
			difference_type current = _current + n;

			if (current >= size || current < 0) {
				_current = -1;
			}
			else {
				_current = current;
			}
		}

		template <typename Class>
		accessible<Class>
		accessible<Class>::operator - (difference_type const& n) const
		{
			difference_type current = _current - n;

			if (current >= size || current < 0) {
				return accessible<Class>(_object, -1);
			}
			else {
				return accessible<Class>(_object, current);
			}
		}

		template <typename Class>
		accessible<Class>&
		accessible<Class>::operator -= (difference_type const& n)
		{
			difference_type current = _current - n;

			if (current >= size || current < 0) {
				_current = -1;
			}
			else {
				_current = current;
			}
		}

		template <typename Class>
		bool
		accessible<Class>::operator == (accessible<Class> const& other) const
		{
			return _object == other._object && _current == other._current;
		}

		template <typename Class>
		bool
		accessible<Class>::operator != (accessible<Class> const& other) const
		{
			return _object != other._object || _current != other._current;
		}

		template <typename Class>
		bool
		accessible<Class>::operator > (accessible<Class> const& other) const
		{
			return _object == other._object && _current > other._current;
		}

		template <typename Class>
		bool
		accessible<Class>::operator >= (accessible<Class> const& other) const
		{
			return _object == other._object && _current >= other._current;
		}

		template <typename Class>
		bool
		accessible<Class>::operator < (accessible<Class> const& other) const
		{
			return _object == other._object && _current < other._current;
		}

		template <typename Class>
		bool
		accessible<Class>::operator <= (accessible<Class> const& other) const
		{
			return _object == other._object && _current <= other._current;
		}
	}
}
