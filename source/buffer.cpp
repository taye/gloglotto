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
	buffer::bound (unsigned target) throw (invalid_enum)
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

	buffer::buffer (unsigned target, unsigned usage, void const* data, size_t size) : buffer()
	{
		set(target, usage, data, size);
	}

	buffer::buffer (unsigned target, unsigned usage, float data) : buffer()
	{
		set(target, usage, data);
	}

	buffer::buffer (unsigned target, unsigned usage, int data) : buffer()
	{
		set(target, usage, data);
	}

	buffer::buffer (unsigned target, unsigned usage, unsigned data) : buffer()
	{
		set(target, usage, data);
	}

	buffer::buffer (unsigned target, unsigned usage, bool data) : buffer()
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
		return buffer::bound(target) == _id;
	}

	buffer const&
	buffer::bind (unsigned target) const throw (invalid_enum) {
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
	buffer::reallocate (unsigned target, unsigned usage, size_t size) const
	{
		glBufferData(target, size, NULL, usage);

		return *this;
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, void const* data, size_t size) const
	{
		bind(target);
		glBufferData(target, size, data, usage);
		unbind(target);

		return *this;
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, float data) const
	{
		return set(target, usage, &data, sizeof(data));
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, int data) const
	{
		return set(target, usage, &data, sizeof(data));
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, unsigned data) const
	{
		return set(target, usage, &data, sizeof(data));
	}

	buffer const&
	buffer::set (unsigned target, unsigned usage, bool data) const
	{
		return set(target, usage, &data, sizeof(data));
	}

	buffer const&
	buffer::replace (unsigned target, void const* data, size_t size, size_t offset) const
	{
		bind(target);
		glBufferSubData(target, offset, size, data);
		unbind(target);

		return *this;
	}

	buffer const&
	buffer::replace (unsigned target, float data, size_t offset) const
	{
		return replace(target, &data, sizeof(data), offset);
	}

	buffer const&
	buffer::replace (unsigned target, int data, size_t offset) const
	{
		return replace(target, &data, sizeof(data), offset);
	}

	buffer const&
	buffer::replace (unsigned target, unsigned data, size_t offset) const
	{
		return replace(target, &data, sizeof(data), offset);
	}

	buffer const&
	buffer::replace (unsigned target, bool data, size_t offset) const
	{
		return replace(target, &data, sizeof(data), offset);
	}
}
