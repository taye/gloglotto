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

#include <gloglotto/buffer>

namespace gloglotto
{
	template <int Size, typename Type>
	buffer::buffer (unsigned target, unsigned usage, vector<Size, Type> const& data) throw (invalid_enum) : buffer(target)
	{
		set(target, usage, data);
	}

	template <int Size, typename Vector>
	buffer::buffer (unsigned target, unsigned usage, vectors<Size, Vector> const& data) throw (invalid_enum) : buffer(target)
	{
		set(target, usage, data);
	}

	template <int Rows, int Columns, typename Type>
	buffer::buffer (unsigned target, unsigned usage, matrix<Rows, Columns, Type> const& data) throw (invalid_enum) : buffer(target)
	{
		set(target, usage, data);
	}

	template <int Size, typename Matrix>
	buffer::buffer (unsigned target, unsigned usage, matrices<Size, Matrix> const& data) throw (invalid_enum) : buffer(target)
	{
		set(target, usage, data);
	}

	template <int Size, typename Type>
	buffer const&
	buffer::set (unsigned target, unsigned usage, vector<Size, Type> const& data) const throw (invalid_enum)
	{
		return set(target, usage, reinterpret_cast<void const*>(&data), sizeof(Type) * vector<Size, Type>::elements);
	}

	template <int Size, typename Vector>
	buffer const&
	buffer::set (unsigned target, unsigned usage, vectors<Size, Vector> const& data) const throw (invalid_enum)
	{
		return set(target, usage, reinterpret_cast<void const*>(&data), sizeof(typename Vector::type) * Size * Vector::elements);
	}

	template <int Rows, int Columns, typename Type>
	buffer const&
	buffer::set (unsigned target, unsigned usage, matrix<Rows, Columns, Type> const& data) const throw (invalid_enum)
	{
		return set(target, usage, reinterpret_cast<void const*>(&data), sizeof(Type) * matrix<Rows, Columns, Type>::elements);
	}

	template <int Size, typename Matrix>
	buffer const&
	buffer::set (unsigned target, unsigned usage, matrices<Size, Matrix> const& data) const throw (invalid_enum)
	{
		return set(target, usage, reinterpret_cast<void const*>(&data), sizeof(typename Matrix::type) * Size * Matrix::elements);
	}

	template <int Size, typename Type>
	buffer const&
	buffer::replace (unsigned target, vector<Size, Type> const& data, size_t offset) const throw (invalid_enum)
	{
		return replace(target, reinterpret_cast<void const*>(&data), sizeof(Type) * vector<Size, Type>::elements, offset);
	}

	template <int Size, typename Vector>
	buffer const&
	buffer::replace (unsigned target, vectors<Size, Vector> const& data, size_t offset) const throw (invalid_enum)
	{
		return replace(target, reinterpret_cast<void const*>(&data), sizeof(typename Vector::type) * Size * Vector::elements, offset);
	}

	template <int Rows, int Columns, typename Type>
	buffer const&
	buffer::replace (unsigned target, matrix<Rows, Columns, Type> const& data, size_t offset) const throw (invalid_enum)
	{
		return replace(target, reinterpret_cast<void const*>(&data), sizeof(Type) * matrix<Rows, Columns, Type>::elements, offset);
	}

	template <int Size, typename Matrix>
	buffer const&
	buffer::replace (unsigned target, matrices<Size, Matrix> const& data, size_t offset) const throw (invalid_enum)
	{
		return replace(target, reinterpret_cast<void const*>(&data), sizeof(typename Matrix::type) * Size * Matrix::elements, offset);
	}

	template <int Size, typename Type>
	buffer&
	buffer::set (unsigned usage, vector<Size, Type> const& data) throw (invalid_enum)
	{
		return set(usage, reinterpret_cast<void const*>(&data), sizeof(Type) * vector<Size, Type>::elements);
	}

	template <int Size, typename Vector>
	buffer&
	buffer::set (unsigned usage, vectors<Size, Vector> const& data) throw (invalid_enum)
	{
		return set(usage, reinterpret_cast<void const*>(&data), sizeof(typename Vector::type) * Size * Vector::elements);
	}

	template <int Rows, int Columns, typename Type>
	buffer&
	buffer::set (unsigned usage, matrix<Rows, Columns, Type> const& data) throw (invalid_enum)
	{
		return set(usage, reinterpret_cast<void const*>(&data), sizeof(Type) * matrix<Rows, Columns, Type>::elements);
	}

	template <int Size, typename Matrix>
	buffer&
	buffer::set (unsigned usage, matrices<Size, Matrix> const& data) throw (invalid_enum)
	{
		return set(usage, reinterpret_cast<void const*>(&data), sizeof(typename Matrix::type) * Size * Matrix::elements);
	}

	template <int Size, typename Type>
	buffer&
	buffer::replace (vector<Size, Type> const& data, size_t offset) throw (invalid_enum)
	{
		return replace(reinterpret_cast<void const*>(&data), sizeof(Type) * vector<Size, Type>::elements, offset);
	}

	template <int Size, typename Vector>
	buffer&
	buffer::replace (vectors<Size, Vector> const& data, size_t offset) throw (invalid_enum)
	{
		return replace(reinterpret_cast<void const*>(&data), sizeof(typename Vector::type) * Size * Vector::elements, offset);
	}

	template <int Rows, int Columns, typename Type>
	buffer&
	buffer::replace (matrix<Rows, Columns, Type> const& data, size_t offset) throw (invalid_enum)
	{
		return replace(reinterpret_cast<void const*>(&data), sizeof(Type) * matrix<Rows, Columns, Type>::elements, offset);
	}

	template <int Size, typename Matrix>
	buffer&
	buffer::replace (matrices<Size, Matrix> const& data, size_t offset) throw (invalid_enum)
	{
		return replace(reinterpret_cast<void const*>(&data), sizeof(typename Matrix::type) * Size * Matrix::elements, offset);
	}
}
