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

#include <gloglotto/object>
#include <gloglotto/headers>

#include <map>

namespace gloglotto
{
	unsigned
	buffer::current (unsigned target) throw (invalid_enum)
	{
		static std::map<unsigned, unsigned> targets = {
			{ target::vertex::data, GL_ARRAY_BUFFER_BINDING },
			{ target::vertex::indices, GL_ELEMENT_ARRAY_BUFFER_BINDING },

			{ target::pixel::pack, GL_PIXEL_PACK_BUFFER_BINDING },
			{ target::pixel::unpack, GL_PIXEL_UNPACK_BUFFER_BINDING },

			{ target::indirect::draw, GL_DRAW_INDIRECT_BUFFER_BINDING },
			{ target::indirect::dispatch, GL_DISPATCH_INDIRECT_BUFFER_BINDING },

			{ target::shader::storage, GL_SHADER_STORAGE_BUFFER_BINDING },
			{ target::shader::uniform, GL_UNIFORM_BUFFER_BINDING }
		};

		if (targets.find(target) == targets.end()) {
			throw invalid_enum();
		}

		unsigned id;

		check_exception {
			glGetIntegerv(targets[target], reinterpret_cast<GLint*>(&id));
		}

		return id;
	}

	buffer::buffer (void)
	{
		glGenBuffers(1, &_id);
	}

	buffer::buffer (unsigned target) throw (invalid_enum) : buffer()
	{
		try {
			bind(target);
		}
		catch (invalid_enum& e) {
			glDeleteBuffers(1, &_id);

			throw;
		}
	}

	buffer::buffer (unsigned target, unsigned usage, void const* data, size_t size) throw (invalid_enum) : buffer(target)
	{
		set(target, usage, data, size);
	}

	buffer::buffer (unsigned target, unsigned usage, float data) throw (invalid_enum) : buffer(target)
	{
		set(target, usage, data);
	}

	buffer::buffer (unsigned target, unsigned usage, int data) throw (invalid_enum) : buffer(target)
	{
		set(target, usage, data);
	}

	buffer::buffer (unsigned target, unsigned usage, unsigned data) throw (invalid_enum) : buffer(target)
	{
		set(target, usage, data);
	}

	buffer::buffer (unsigned target, unsigned usage, bool data) throw (invalid_enum) : buffer(target)
	{
		set(target, usage, data);
	}

	buffer::~buffer (void)
	{
		glDeleteBuffers(1, &_id);
	}

	bool
	buffer::bound (unsigned target) const throw (invalid_enum)
	{
		return buffer::current(target) == _id;
	}

	buffer const&
	buffer::bind (unsigned target) const throw (invalid_enum)
	{
		check_exception {
			glBindBuffer(target, _id);
		}

		return *this;
	}

	buffer const&
	buffer::unbind (unsigned target) const throw (invalid_enum)
	{
		check_exception {
			glBindBuffer(target, 0);
		}

		return *this;
	}

	buffer const&
	buffer::reallocate (unsigned target, unsigned usage, size_t size) const throw (invalid_enum)
	{
		check_exception {
			glBufferData(target, size, NULL, usage);
		}

		return *this;
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, void const* data, size_t size) const throw (invalid_enum)
	{
		glBufferData(target, size, data, usage);

		return *this;
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, float data) const throw (invalid_enum)
	{
		return set(target, usage, &data, sizeof(data));
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, int data) const throw (invalid_enum)
	{
		return set(target, usage, &data, sizeof(data));
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, unsigned data) const throw (invalid_enum)
	{
		return set(target, usage, &data, sizeof(data));
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, bool data) const throw (invalid_enum)
	{
		return set(target, usage, &data, sizeof(data));
	}

	buffer const&
	buffer::replace (unsigned target, void const* data, size_t size, size_t offset) const throw (invalid_enum)
	{
		glBufferSubData(target, offset, size, data);

		return *this;
	}

	buffer const&
	buffer::replace (unsigned target, float data, size_t offset) const throw (invalid_enum)
	{
		return replace(target, &data, sizeof(data), offset);
	}

	buffer const&
	buffer::replace (unsigned target, int data, size_t offset) const throw (invalid_enum)
	{
		return replace(target, &data, sizeof(data), offset);
	}

	buffer const&
	buffer::replace (unsigned target, unsigned data, size_t offset) const throw (invalid_enum)
	{
		return replace(target, &data, sizeof(data), offset);
	}

	buffer const&
	buffer::replace (unsigned target, bool data, size_t offset) const throw (invalid_enum)
	{
		return replace(target, &data, sizeof(data), offset);
	}

	buffer&
	buffer::bind (unsigned target) throw (invalid_enum)
	{
		check_exception {
			glBindBuffer(target, _id);
		}

		_target = target;

		return *this;
	}

	buffer&
	buffer::unbind (void) throw (invalid_enum)
	{
		check_exception {
			glBindBuffer(_target, 0);
		}

		_target = 0;

		return *this;
	}

	buffer&
	buffer::reallocate (unsigned usage, size_t size) throw (invalid_enum)
	{
		check_exception {
			glBufferData(_target, size, NULL, usage);
		}

		return *this;
	}

	buffer&
	buffer::set (unsigned usage, void const* data, size_t size) throw (invalid_enum)
	{
		glBufferData(_target, size, data, usage);

		return *this;
	}

	buffer&
	buffer::set (unsigned usage, float data) throw (invalid_enum)
	{
		return set(usage, &data, sizeof(data));
	}

	buffer&
	buffer::set (unsigned usage, int data) throw (invalid_enum)
	{
		return set(usage, &data, sizeof(data));
	}

	buffer&
	buffer::set (unsigned usage, unsigned data) throw (invalid_enum)
	{
		return set(usage, &data, sizeof(data));
	}

	buffer&
	buffer::set (unsigned usage, bool data) throw (invalid_enum)
	{
		return set(usage, &data, sizeof(data));
	}

	buffer&
	buffer::replace (void const* data, size_t size, size_t offset) throw (invalid_enum)
	{
		glBufferSubData(_target, offset, size, data);

		return *this;
	}

	buffer&
	buffer::replace (float data, size_t offset) throw (invalid_enum)
	{
		return replace(&data, sizeof(data), offset);
	}

	buffer&
	buffer::replace (int data, size_t offset) throw (invalid_enum)
	{
		return replace(&data, sizeof(data), offset);
	}

	buffer&
	buffer::replace (unsigned data, size_t offset) throw (invalid_enum)
	{
		return replace(&data, sizeof(data), offset);
	}

	buffer&
	buffer::replace (bool data, size_t offset) throw (invalid_enum)
	{
		return replace(&data, sizeof(data), offset);
	}
}
