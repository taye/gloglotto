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

#include <gloglotto/thin>
#include <gloglotto/extension>

#include <iterator>
#include <sstream>
#include <algorithm>

namespace gloglotto
{
	namespace extension
	{
		std::vector<std::string>
		list (void)
		{
			std::vector<std::string> result;
			std::istringstream       stream(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)));

			std::copy(std::istream_iterator<std::string>(stream),
			          std::istream_iterator<std::string>(),
			          std::back_inserter<std::vector<std::string>>(result));

			return result;
		}

		bool
		supported (std::string name)
		{
			return glewIsSupported(name.c_str());
		}
	}
}
