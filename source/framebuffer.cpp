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

#include <gloglotto/framebuffer>

namespace gloglotto
{
	framebuffer::framebuffer (void)
	{
		glGenFramebuffers(1, &_id);
	}

	framebuffer::~framebuffer (void)
	{
		glDeleteFramebuffers(1, &_id);
	}

	framebuffer const&
	framebuffer::bind (unsigned target) const throw (invalid_enum)
	{
		check_exception {
			glBindFramebuffer(target, _id);
		}

		return *this;
	}

	framebuffer const&
	framebuffer::unbind (unsigned target) const throw (invalid_enum)
	{
		check_exception {
			glBindFramebuffer(target, 0);
		}

		return *this;
	}

	framebuffer&
	framebuffer::bind (unsigned target) throw (invalid_enum)
	{
		check_exception {
			glBindFramebuffer(target, _id);
		}

		_target = target;

		return *this;
	}

	framebuffer&
	framebuffer::unbind (void) throw (invalid_enum)
	{
		check_exception {
			glBindFramebuffer(_target, _id);
		}

		_target = 0;

		return *this;
	}
}
