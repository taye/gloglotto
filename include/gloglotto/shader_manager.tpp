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
		if (_shaders.find(name) != _shaders.end()) {
			throw invalid_operation("shader already registered");
		}

		return *(_shaders[name] = make(source, lambda));
	}

	template <typename ...Args>
	shader_manager::shader_in_use
	shader_manager::use (std::string name, Args... args)
	{
		auto current = _shaders.at(name);

		current->begin(args...);

		return shader_in_use(current);
	}

	template <typename Type>
	shader_manager::shader_in_use&
	shader_manager::shader_in_use::attribute (std::string name, size_t offset, int stride, bool normalized) throw (invalid_value)
	{
		if (!_vertex_array) {
			_vertex_array = new vertex_array();
		}

		unsigned location = _shader->attribute(name);

		_vertex_array->bind();
		_vertex_array->enable(location);
		_vertex_array->define<Type>(location, offset, stride, normalized);

		return *this;
	}

	template <typename Type>
	shader_manager::shader_in_use&
	shader_manager::shader_in_use::attribute (std::string name, buffer const& buffer, size_t offset, int stride, bool normalized) throw (invalid_value)
	{
		buffer.bind(target::vertex::data);
		attribute<Type>(name, offset, stride, normalized);
		buffer.unbind(target::vertex::data);

		return *this;
	}
}
