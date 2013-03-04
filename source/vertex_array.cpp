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

#include <gloglotto/object>
#include <gloglotto/headers>

namespace gloglotto
{
	vertex_array::vertex_array (void)
	{
		glGenVertexArrays(1, &_id);
	}

	vertex_array::~vertex_array (void)
	{
		glDeleteBuffers(1, &_id);
	}

	vertex_array const&
	vertex_array::bind (void) const throw (invalid_operation)
	{
		check_exception {
			glBindVertexArray(_id);
		}

		return *this;
	}

	vertex_array const&
	vertex_array::unbind (void) const throw (invalid_operation)
	{
		check_exception {
			glBindVertexArray(0);
		}

		return *this;
	}

	vertex_array const&
	vertex_array::enable (unsigned index) const throw (invalid_value, invalid_operation)
	{
		glEnableVertexAttribArray(index);

		return *this;
	}

	vertex_array const&
	vertex_array::disable (unsigned index) const throw (invalid_value, invalid_operation)
	{
		glDisableVertexAttribArray(index);

		return *this;
	}
}
