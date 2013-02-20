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

#include <gloglotto/maths/matrix>
#include <gloglotto/maths/vector>

#include <cmath>
#include <algorithm>

namespace gloglotto
{
	namespace math
	{
		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::matrix (void)
		{
			_data      = new Type[Columns * Rows];
			_allocated = true;

			std::fill(_data, _data + Columns * Rows, 0);
			std::fill(_vectors, _vectors + Rows, nullptr);

			if (Columns == 2 && Rows == 2) {
				_data[0] = 1.0; _data[1] = 0.0;
				_data[2] = 0.0; _data[3] = 1.0;
			}
			else if (Columns == 3 && Rows == 3) {
				_data[0] = 1.0; _data[1] = 0.0; _data[2] = 0.0;
				_data[3] = 0.0; _data[4] = 1.0; _data[5] = 0.0;
				_data[6] = 0.0; _data[7] = 0.0; _data[8] = 1.0;
			}
			else if (Columns == 4 && Rows == 4) {
				_data[0]  = 1.0; _data[1]  = 0.0; _data[2]  = 0.0; _data[3]  = 0.0;
				_data[4]  = 0.0; _data[5]  = 1.0; _data[6]  = 0.0; _data[7]  = 0.0;
				_data[8]  = 0.0; _data[9]  = 0.0; _data[10] = 1.0; _data[11] = 0.0;
				_data[12] = 0.0; _data[13] = 0.0; _data[14] = 0.0; _data[15] = 1.0;
			}
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::matrix (Type init)
		{
			_data      = new Type[Columns * Rows];
			_allocated = true;

			std::fill(_data, _data + Columns * Rows, init);
			std::fill(_vectors, _vectors + Rows, nullptr);
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::matrix (matrix<Columns, Rows, Type> const& from)
		{
			_data      = new Type[Columns * Rows];
			_allocated = true;

			std::fill(_vectors, _vectors + Rows, nullptr);
			std::move(&from, &from + Columns * Rows, _data);
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::matrix (Type* data)
		{
			_data      = data;
			_allocated = false;

			std::fill(_vectors, _vectors + Rows, nullptr);
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::matrix (std::initializer_list<std::initializer_list<Type>> list) throw (std::invalid_argument)
		{
			_data      = new Type[Columns * Rows];
			_allocated = true;

			std::fill(_vectors, _vectors + Rows, nullptr);

			*this = list;
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>::~matrix (void)
		{
			if (_allocated) {
				delete[] _data;
			}

			for (int i = 0; i < Rows; i++) {
				if (_vectors[i]) {
					delete _vectors[i];
				}
			}
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>&
		matrix<Columns, Rows, Type>::operator = (matrix<Columns, Rows, Type> const& from)
		{
			std::move(&from, &from + Columns * Rows, _data);
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>&
		matrix<Columns, Rows, Type>::operator = (const Type* data)
		{
			std::move(data, data + Columns * Rows, _data);
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>&
		matrix<Columns, Rows, Type>::operator = (std::initializer_list<std::initializer_list<Type>> list) throw (std::invalid_argument)
		{
			if (list.size() != Rows) {
				throw std::invalid_argument("number of arguments doesn't match matrix rows");
			}

			int i = 0;
			for (auto list : list) {
				if (list.size() != Columns) {
					throw std::invalid_argument("number of arguments doesn't match matrix columns");
				}

				int j = 0;
				for (auto value : list) {
					_data[i * Columns + j] = value;

					j++;
				}

				i++;
			}

			return *this;
		}

		template <int Columns, int Rows, typename Type>
		vector<Columns, Type>&
		matrix<Columns, Rows, Type>::operator [] (int index)
		{
			if (index < 0 || index >= Rows) {
				throw std::out_of_range("index out of range");
			}

			if (!_vectors[index]) {
				_vectors[index] = new vector<Columns, Type>(_data + (Columns * index));
			}

			return *_vectors[index];
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>
		matrix<Columns, Rows, Type>::operator + (matrix<Columns, Rows, Type> const& other) const
		{
			return matrix<Columns, Rows, Type>(this) += other;
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>&
		matrix<Columns, Rows, Type>::operator += (matrix<Columns, Rows, Type> const& other)
		{
			for (int i = 0; i < Rows; i++) {
				for (int j = 0; j < Columns; j++) {
					_data[j * Columns + i] += (&other)[i * Rows + j];
				}
			}

			return *this;
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>
		matrix<Columns, Rows, Type>::operator - (matrix<Columns, Rows, Type> const& other) const
		{
			return matrix<Columns, Rows, Type>(this) -= other;
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>&
		matrix<Columns, Rows, Type>::operator -= (matrix<Columns, Rows, Type> const& other)
		{
			for (int i = 0; i < Rows; i++) {
				for (int j = 0; j < Columns; j++) {
					_data[j * Columns + i] -= (&other)[i * Rows + j];
				}
			}

			return *this;
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>
		matrix<Columns, Rows, Type>::operator * (Type other) const
		{
			return matrix<Columns, Rows, Type>(this) *= other;
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>&
		matrix<Columns, Rows, Type>::operator *= (Type other)
		{
			for (int i = 0; i < Rows; i++) {
				for (int j = 0; j < Columns; j++) {
					_data[j * Columns + i] *= other;
				}
			}

			return *this;
		}

		template <int Columns, int Rows, typename Type>
		template <int OtherColumns, int OtherRows>
		matrix<OtherColumns, Rows, Type>
		matrix<Columns, Rows, Type>::operator * (matrix<OtherColumns, OtherRows, Type> const& other) const
		{
			static_assert(Columns == OtherRows, "left column length and right row length must be the same");

			matrix<OtherColumns, Rows, Type> result;

			for (int i = 0; i < OtherColumns; i++) {
				for (int j = 0; j < Rows; j++) {
					Type element = 0;

					for (int h = 0; h < Columns; h++) {
						element += _data[j * Columns + h] * (&other)[j * Columns + i];
					}

					(&result)[j * OtherColumns + i] = element;
				}
			}

			return result;
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>&
		matrix<Columns, Rows, Type>::operator *= (matrix<Columns, Rows, Type> const& other)
		{
			*this = this * other;

			return *this;
		}

		template <int Columns, int Rows, typename Type>
		matrix<Columns, Rows, Type>
		matrix<Columns, Rows, Type>::operator ~ (void) const throw (std::logic_error)
		{
			static_assert(Columns == Rows, "only square matrices are invertible");
		}

		template <int Columns, int Rows, typename Type>
		Type*
		matrix<Columns, Rows, Type>::operator & (void) const
		{
			return _data;
		}
	}
}
