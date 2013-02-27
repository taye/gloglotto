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

#include <gloglotto/shader_manager>
#include <gloglotto/utility>

namespace gloglotto
{
	template <typename Function>
	shader*
	shader_manager::make (std::multimap<std::string, std::string> source, Function lambda) throw (invalid_operation, failed_compilation, failed_linking)
	{
		return new shader(source, lambda);
	}

	template <typename Function>
	shader&
	shader_manager::add (std::string name, std::multimap<std::string, std::string> source, Function lambda) throw (invalid_operation, failed_compilation, failed_linking)
	{
		auto current = make(source, lambda);

		_shaders[name] = current;

		return *current;
	}

	template <typename ...Args>
	shader_manager::shader_in_use
	shader_manager::use (std::string name, Args... args)
	{
		auto current = _shaders.at(name);

		current->begin(args...);

		return shader_in_use(current);
	}
}
