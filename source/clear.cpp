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

#include <gloglotto/clear>

namespace gloglotto
{
	void
	clear (enum clear mask) throw (invalid_value, invalid_operation)
	{
		check_exception {
			glClear(static_cast<unsigned int>(mask));
		}
	}

	void
	clear (enum clear mask, float red, float green, float blue, float alpha) throw (invalid_value, invalid_operation)
	{
		unsigned int bitmask = static_cast<unsigned int>(mask);

		if (bitmask & ~(GL_COLOR_BUFFER_BIT | GL_ACCUM_BUFFER_BIT)) {
			throw invalid_value("can only set color and accumulation bits");
		}

		if (bitmask & GL_COLOR_BUFFER_BIT) {
			check_exception {
				glClearColor(red, green, blue, alpha);
			}
		}

		if (bitmask & GL_ACCUM_BUFFER_BIT) {
			check_exception {
				glClearAccum(red, green, blue, alpha);
			}
		}
	}

	void
	clear (enum clear mask, float red, float green, float blue) throw (invalid_value, invalid_operation)
	{
		clear(mask, red, green, blue, 1.0);
	}

	void
	clear (enum clear mask, double depth) throw (invalid_value, invalid_operation)
	{
		unsigned int bitmask = static_cast<unsigned int>(mask);

		if (bitmask & ~GL_DEPTH_BUFFER_BIT) {
			throw invalid_value("can only set depth bits");
		}

		check_exception {
			glClearDepth(depth);
		}
	}

	void
	clear (enum clear mask, float index) throw (invalid_value, invalid_operation)
	{
		unsigned int bitmask = static_cast<unsigned int>(mask);

		if (bitmask & ~GL_COLOR_BUFFER_BIT) {
			throw invalid_value("can only set colors bits");
		}

		check_exception {
			glClearIndex(index);
		}
	}

	void
	clear (enum clear mask, int index) throw (invalid_value, invalid_operation)
	{
		unsigned int bitmask = static_cast<unsigned int>(mask);

		if (bitmask & ~GL_STENCIL_BUFFER_BIT) {
			throw invalid_value("can only set stencil bits");
		}

		check_exception {
			glClearStencil(index);
		}
	}
}
