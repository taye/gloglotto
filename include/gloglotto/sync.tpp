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
	template <>
	inline
	sync::status
	sync::wait<sync::server> (unsigned timeout) throw (std::invalid_argument)
	{
		if (timeout != 0) {
			throw std::invalid_argument("server wait doesn't support timeout");
		}

		glWaitSync(_sync, 0, GL_TIMEOUT_IGNORED);

		return status::condition_satisfied;
	}

	template <>
	inline
	sync::status
	sync::wait<sync::client> (unsigned timeout) throw (std::invalid_argument)
	{
		return static_cast<status>(glClientWaitSync(_sync, GL_SYNC_FLUSH_COMMANDS_BIT, timeout));
	}
}
