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

namespace gloglotto
{
	shader_manager::shader_manager (void)
	{
	}

	shader_manager::~shader_manager (void)
	{
		for (auto entry : _shaders) {
			delete entry.second;
		}
	}

	shader*
	shader_manager::make (std::multimap<std::string, std::string> source) throw (invalid_operation, failed_compilation, failed_linking)
	{
		return new shader(source);
	}

	shader&
	shader_manager::add (std::string name, std::multimap<std::string, std::string> source) throw (invalid_operation, failed_compilation, failed_linking)
	{
		auto current = make(source);

		_shaders[name] = current;

		return *current;
	}

	shader&
	shader_manager::get (std::string name)
	{
		return *_shaders.at(name);
	}

	shader_manager::shader_in_use::shader_in_use (shader* in_use)
	{
		_shader = in_use;

		_vertex_array = nullptr;
		_owner        = false;
	}

	shader_manager::shader_in_use::~shader_in_use (void)
	{
		if (_vertex_array) {
			_vertex_array->unbind();

			if (_owner) {
				delete _vertex_array;
			}
		}
	}

	shader_manager::shader_in_use&
	shader_manager::shader_in_use::with (vertex_array const* vertex_array)
	{
		if (_owner && _vertex_array) {
			delete _vertex_array;
		}

		_vertex_array = const_cast<class vertex_array*>(vertex_array);
		_owner        = false;

		return *this;
	}

	shader_manager::shader_in_use&
	shader_manager::shader_in_use::use (buffer const& buffer)
	{
		buffer.bind(target::vertex::data);

		return *this;
	}

	shader_manager::shader_in_use&
	shader_manager::shader_in_use::draw (unsigned primitive, size_t count, size_t offset) throw (invalid_enum, invalid_value, invalid_operation)
	{
		check_exception {
			glDrawArrays(primitive, offset, count);
		}

		return *this;
	}

	shader_manager::shader_in_use*
	shader_manager::shader_in_use::begin (void)
	{
		return this;
	}

	shader_manager::shader_in_use*
	shader_manager::shader_in_use::end (void)
	{
		return this + 1;
	}

	shader*
	shader_manager::shader_in_use::operator -> (void)
	{
		return _shader;
	}
}
