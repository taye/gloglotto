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

#include <gloglotto/matrices>

namespace gloglotto
{
	template <int Size, class Matrix>
	matrices<Size, Matrix>::matrices (void)
	{
		_data      = new type[Size * rows * columns];
		_allocated = true;

		std::fill(_data, _data + Size * rows * columns, 0);
		std::fill(_matrices, _matrices + Size, nullptr);
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>::matrices (type* pointer)
	{
		_data      = pointer;
		_allocated = false;

		std::fill(_matrices, _matrices + Size, nullptr);
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>::matrices (matrices<Size, Matrix> const& from)
	{
		_data      = new type[Size * rows * columns];
		_allocated = true;

		std::move(&from, &from + Size * rows * columns, _data);
		std::fill(_matrices, _matrices + Size, nullptr);
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>::matrices (std::initializer_list<Matrix> list)
	{
		_data      = new type[Size * rows * columns];
		_allocated = true;

		std::fill(_matrices, _matrices + Size, nullptr);

		try {
			*this = list;
		}
		catch (std::invalid_argument& e) {
			delete[] _data;

			throw e;
		}
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>::~matrices (void)
	{
		if (_allocated) {
			delete[] _data;
		}

		for (int i = 0; i < Size; i++) {
			if (_matrices[i]) {
				delete _matrices[i];
			}
		}
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::operator = (matrices<Size, Matrix> const& from)
	{
		std::move(&from, &from + Size * rows * columns, _data);

		return *this;
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::operator = (const type* from)
	{
		std::move(from, from + Size * rows * columns, _data);

		return *this;
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::operator = (std::initializer_list<Matrix> list) throw (std::invalid_argument)
	{
		if (list.size() != Size) {
			throw std::invalid_argument("number of arguments doesn't match matrices size");
		}

		int i = 0;
		for (auto matrix : list) {
			(*this)[i] = matrix;
		}

		return *this;
	}

	template <int Size, class Matrix>
	Matrix&
	matrices<Size, Matrix>::operator [] (int index) throw (std::out_of_range)
	{
		if (index < 0 || index >= Size) {
			throw std::out_of_range("index out of range");
		}

		if (!_matrices[index]) {
			_matrices[index] = new Matrix(_data + (rows * columns * index));
		}

		return *_matrices[index];
	}

	template <int Size, class Matrix>
	typename matrices<Size, Matrix>::iterator
	matrices<Size, Matrix>::begin (void)
	{
		return iterator(this);
	}

	template <int Size, class Matrix>
	typename matrices<Size, Matrix>::iterator
	matrices<Size, Matrix>::end (void)
	{
		return iterator(this, -1);
	}

	template <int Size, class Matrix>
	typename matrices<Size, Matrix>::type*
	matrices<Size, Matrix>::operator & (void) const
	{
		return _data;
	}
}