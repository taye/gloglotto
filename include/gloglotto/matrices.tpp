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
		_data     = new type[Size * rows * columns];
		_matrices = nullptr;

		std::fill(_data, _data + Size * rows * columns, 0);

		own();
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>::matrices (type* pointer)
	{
		_data     = pointer;
		_matrices = nullptr;

		disown();
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>::matrices (matrices<Size, Matrix> const& from)
	{
		_data     = new type[Size * rows * columns];
		_matrices = nullptr;

		std::copy(&from, &from + Size * rows * columns, _data);

		own();
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>::matrices (std::initializer_list<std::initializer_list<std::initializer_list<type>>> list) throw (std::invalid_argument)
	{
		_data     = new type[Size * rows * columns];
		_matrices = nullptr;

		try {
			*this = list;
		}
		catch (std::invalid_argument& e) {
			delete[] _data;

			throw e;
		}

		own();
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>::~matrices (void)
	{
		if (owner()) {
			delete[] _data;
		}

		if (_matrices) {
			for (int i = 0; i < Size; i++) {
				if (_matrices[i]) {
					delete _matrices[i];
				}
			}
		}
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::operator = (matrices<Size, Matrix> const& from)
	{
		std::copy(&from, &from + Size * rows * columns, _data);

		return *this;
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::operator = (matrices<Size, Matrix>&& from)
	{
		return swap(from);
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::operator = (const type* from)
	{
		std::copy(from, from + Size * rows * columns, _data);

		return *this;
	}

	template <int Size, class Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::operator = (std::initializer_list<std::initializer_list<std::initializer_list<type>>> list) throw (std::invalid_argument)
	{
		if (list.size() != Size) {
			throw std::invalid_argument("number of arguments doesn't match matrices size");
		}

		int i = 0;
		for (auto matrix : list) {
			int row = 0;
			for (auto list : matrix) {
				int column = 0;
				for (auto value : list) {
					_data[i * elements + row * columns + column] = value;

					column++;
				}

				row++;
			}

			i++;
		}

		return *this;
	}

	template <int Size, typename Matrix>
	bool
	matrices<Size, Matrix>::owner (void) const
	{
		return _owner;
	}

	template <int Size, typename Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::own (void)
	{
		_owner = true;

		return *this;
	}

	template <int Size, typename Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::disown (void)
	{
		_owner = false;

		return *this;
	}

	template <int Size, typename Matrix>
	matrices<Size, Matrix>&
	matrices<Size, Matrix>::swap (matrices<Size, Matrix>& other)
	{
		auto data     = _data;
		auto owner    = _owner;
		auto matrices = _matrices;

		_data     = other._data;
		_owner    = other._owner;
		_matrices = other._matrices;

		other._data     = data;
		other._owner    = owner;
		other._matrices = matrices;

		return *this;
	}

	template <int Size, class Matrix>
	Matrix const&
	matrices<Size, Matrix>::operator [] (int index) const throw (std::out_of_range)
	{
		if (index < 0 || index >= Size) {
			throw std::out_of_range("index out of range");
		}

		if (!_matrices) {
			_matrices = new Matrix*[Size];
			std::fill(_matrices, _matrices + Size, nullptr);
		}

		if (!_matrices[index]) {
			_matrices[index] = new Matrix(_data + (rows * columns * index));
		}

		return *_matrices[index];
	}

	template <int Size, class Matrix>
	typename matrices<Size, Matrix>::const_iterator
	matrices<Size, Matrix>::begin (void) const
	{
		return const_iterator(this);
	}

	template <int Size, class Matrix>
	typename matrices<Size, Matrix>::const_iterator
	matrices<Size, Matrix>::end (void) const
	{
		return const_iterator(this, -1);
	}

	template <int Size, class Matrix>
	Matrix&
	matrices<Size, Matrix>::operator [] (int index) throw (std::out_of_range)
	{
		if (index < 0 || index >= Size) {
			throw std::out_of_range("index out of range");
		}

		if (!_matrices) {
			_matrices = new Matrix*[Size];
			std::fill(_matrices, _matrices + Size, nullptr);
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
	template <int SliceSize>
	matrices<SliceSize, Matrix>
	matrices<Size, Matrix>::slice (int offset) throw (std::out_of_range)
	{
		if (offset + SliceSize > Size) {
			throw std::out_of_range("slice out of range");
		}

		return matrices<SliceSize, Matrix>(_data + (offset * elements));
	}

	template <int Size, class Matrix>
	typename matrices<Size, Matrix>::type*
	matrices<Size, Matrix>::operator & (void)
	{
		return _data;
	}

	template <int Size, class Matrix>
	typename matrices<Size, Matrix>::type const*
	matrices<Size, Matrix>::operator & (void) const
	{
		return _data;
	}
}
