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

#include <gloglotto/exception>
#include <gloglotto/thin>

namespace gloglotto
{
	void
	raise (void)
	{
		GLenum error = thin::error::code();

		switch (error) {
			case GL_INVALID_ENUM:
				throw invalid_enum(thin::error::string(error));

			case GL_INVALID_VALUE:
				throw invalid_value(thin::error::string(error));

			case GL_INVALID_OPERATION:
				throw invalid_operation(thin::error::string(error));

			case GL_STACK_OVERFLOW:
				throw stack_overflow(thin::error::string(error));

			case GL_STACK_UNDERFLOW:
				throw stack_underflow(thin::error::string(error));

			case GL_OUT_OF_MEMORY:
				throw out_of_memory(thin::error::string(error));

			case GL_TABLE_TOO_LARGE:
				throw table_too_large(thin::error::string(error));
		}
	}
}
