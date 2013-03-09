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

#include <gloglotto/renderbuffer>

namespace gloglotto
{
	renderbuffer::renderbuffer (void)
	{
		glGenRenderbuffers(1, &_id);
	}

	renderbuffer::~renderbuffer (void)
	{
		glDeleteRenderbuffers(1, &_id);
	}

	renderbuffer const&
	renderbuffer::bind (void) const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, _id);

		return *this;
	}

	renderbuffer const&
	renderbuffer::unbind (void) const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		return *this;
	}
}
