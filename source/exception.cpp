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

#include <gloglotto/headers>
#include <gloglotto/exception>

namespace gloglotto
{
	void
	exception::raise (void)
	{
		switch (glGetError()) {
			case GL_INVALID_ENUM:
				throw invalid_enum();

			case GL_INVALID_VALUE:
				throw invalid_value();

			case GL_INVALID_OPERATION:
				throw invalid_operation();

			case GL_STACK_OVERFLOW:
				throw stack_overflow();

			case GL_STACK_UNDERFLOW:
				throw stack_underflow();

			case GL_OUT_OF_MEMORY:
				throw out_of_memory();

			case GL_TABLE_TOO_LARGE:
				throw table_too_large();
		}
	}

	void
	exception::raise (std::string text)
	{
		switch (glGetError()) {
			case GL_INVALID_ENUM:
				throw invalid_enum(text);

			case GL_INVALID_VALUE:
				throw invalid_value(text);

			case GL_INVALID_OPERATION:
				throw invalid_operation(text);

			case GL_STACK_OVERFLOW:
				throw stack_overflow(text);

			case GL_STACK_UNDERFLOW:
				throw stack_underflow(text);

			case GL_OUT_OF_MEMORY:
				throw out_of_memory(text);

			case GL_TABLE_TOO_LARGE:
				throw table_too_large(text);
		}
	}
}
