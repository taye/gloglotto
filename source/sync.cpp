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

#include <gloglotto/sync>

namespace gloglotto
{
	sync::sync (void)
	{
		_sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	}

	sync::~sync (void)
	{
		glDeleteSync(_sync);
	}

	bool
	sync::signaled (void)
	{
		GLint result = GL_UNSIGNALED;
		glGetSynciv(_sync, GL_SYNC_STATUS, sizeof(GLint), NULL, &result);

		return result == GL_SIGNALED;
	}

	void
	flush (void)
	{
		glFlush();
	}

	void
	finish (void)
	{
		glFinish();
	}
}
