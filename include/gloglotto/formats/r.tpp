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

#include <gloglotto/formats/r>

namespace gloglotto
{
	namespace image
	{
		namespace format
		{
			template <int Depth, typename Type, bool Normalized>
			r<Depth, Type, Normalized>::r (size_t size)
				: internal(size * bytes), _size(size)
			{}

			template <int Depth, typename Type, bool Normalized>
			r<Depth, Type, Normalized>::r (void* buffer, size_t size)
				: internal(buffer, size * bytes), _size(size)
			{}

			template <int Depth, typename Type, bool Normalized>
			size_t
			r<Depth, Type, Normalized>::size (void) const
			{
				return _size;
			}

			template <int Depth, typename Type, bool Normalized>
			typename r<Depth, Type, Normalized>::value const*
			r<Depth, Type, Normalized>::operator [] (size_t index) const throw (std::out_of_range)
			{
				if (index >= _size) {
					throw std::out_of_range("index out of range");
				}

				return reinterpret_cast<value*>(_buffer + (index * bytes));
			}

			template <int Depth, typename Type, bool Normalized>
			typename r<Depth, Type, Normalized>::const_iterator
			r<Depth, Type, Normalized>::begin (void) const
			{
				return const_iterator(this);
			}

			template <int Depth, typename Type, bool Normalized>
			typename r<Depth, Type, Normalized>::const_iterator
			r<Depth, Type, Normalized>::end (void) const
			{
				return const_iterator(this, -1);
			}

			template <int Depth, typename Type, bool Normalized>
			typename r<Depth, Type, Normalized>::value*
			r<Depth, Type, Normalized>::operator [] (size_t index) throw (std::out_of_range)
			{
				if (index >= _size) {
					throw std::out_of_range("index out of range");
				}

				return reinterpret_cast<value*>(_buffer + (index * bytes));
			}

			template <int Depth, typename Type, bool Normalized>
			typename r<Depth, Type, Normalized>::iterator
			r<Depth, Type, Normalized>::begin (void)
			{
				return iterator(this);
			}

			template <int Depth, typename Type, bool Normalized>
			typename r<Depth, Type, Normalized>::iterator
			r<Depth, Type, Normalized>::end (void)
			{
				return iterator(this, -1);
			}
		}
	}
}
