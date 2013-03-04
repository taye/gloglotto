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

#include <gloglotto/vertex_array>

namespace gloglotto
{
	template <>
	inline
	vertex_array const&
	vertex_array::define<char> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_BYTE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<unsigned char> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_UNSIGNED_BYTE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<short> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_SHORT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<unsigned short> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_UNSIGNED_SHORT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<int> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<unsigned> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_UNSIGNED_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<bool> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_BYTE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<float> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_FLOAT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<double> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_DOUBLE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<1, bool>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_BYTE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<2, bool>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 2, GL_BYTE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<3, bool>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 3, GL_BYTE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<4, bool>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 4, GL_BYTE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<1, int>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<2, int>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 2, GL_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<3, int>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 3, GL_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<4, int>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 4, GL_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<1, unsigned>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_UNSIGNED_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<2, unsigned>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 2, GL_UNSIGNED_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<3, unsigned>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 3, GL_UNSIGNED_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<4, unsigned>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 4, GL_UNSIGNED_INT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<1, float>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_FLOAT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<2, float>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 2, GL_FLOAT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<3, float>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 3, GL_FLOAT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<4, float>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 4, GL_FLOAT, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<1, double>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 1, GL_DOUBLE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<2, double>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 2, GL_DOUBLE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<3, double>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 3, GL_DOUBLE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}

	template <>
	inline
	vertex_array const&
	vertex_array::define<vector<4, double>> (unsigned index, size_t offset, int stride, bool normalized) const throw (invalid_value)
	{
		glVertexAttribPointer(index, 4, GL_DOUBLE, normalized, stride, reinterpret_cast<void*>(offset));

		return *this;
	}
}
