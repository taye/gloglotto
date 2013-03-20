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

#include <gloglotto/image>

#include <algorithm>

namespace gloglotto
{
	namespace image
	{
		namespace format
		{
			internal::internal (size_t byte_size) :
				_buffer(new char[byte_size]),
				_byte_size(byte_size),
				_owner(true)
			{
				std::fill_n(_buffer, byte_size, 0);
			}

			internal::internal (void* buffer, size_t byte_size) :
				_buffer(static_cast<char*>(buffer)),
				_byte_size(byte_size),
				_owner(false)
			{}

			internal::~internal (void)
			{
				if (owner()) {
					delete[] _buffer;
				}
			}

			bool
			internal::owner (void) const
			{
				return _owner;
			}

			internal&
			internal::own (void)
			{
				_owner = true;

				return *this;
			}

			internal&
			internal::disown (void)
			{
				_owner = false;

				return *this;
			}

			size_t
			internal::byte_size (void) const
			{
				return _byte_size;
			}

			void const*
			internal::operator & (void) const
			{
				return _buffer;
			}

			void*
			internal::operator & (void)
			{
				return _buffer;
			}
		}
	}
}
