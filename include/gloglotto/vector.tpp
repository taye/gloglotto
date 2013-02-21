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

#include <gloglotto/math>

#include <cmath>
#include <algorithm>

namespace gloglotto
{
	template <int Size, typename Type>
	vector<Size, Type>::vector (void)
	{
		_data      = new Type[Size];
		_allocated = true;

		std::fill(_data, _data + Size, 0);
	}

	template <int Size, typename Type>
	vector<Size, Type>::vector (vector<Size, Type> const& from)
	{
		_data      = new Type[Size];
		_allocated = true;

		std::move(&from, &from + Size, _data);
	}

	template <int Size, typename Type>
	vector<Size, Type>::vector (std::initializer_list<Type> list) throw (std::invalid_argument)
	{
		_data      = new Type[Size];
		_allocated = true;

		try {
			*this = list;
		}
		catch (std::invalid_argument& e) {
			delete[] _data;

			throw e;
		}
	}

	template <int Size, typename Type>
	vector<Size, Type>::vector (Type* data)
	{
		_data      = data;
		_allocated = false;
	}

	template <int Size, typename Type>
	vector<Size, Type>::~vector (void)
	{
		if (_allocated) {
			delete _data;
		}
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator = (vector<Size, Type> const& from)
	{
		std::move(&from, &from + Size, _data);

		return *this;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator = (const Type* data)
	{
		std::move(data, data + Size, _data);

		return *this;
	}
	
	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator = (std::initializer_list<Type> list) throw (std::invalid_argument)
	{
		if (list.size() != Size) {
			throw std::invalid_argument("number of arguments doesn't match vector size");
		}

		int i = 0;
		for (auto value : list) {
			_data[i++] = value;
		}

		return *this;
	}

	template <int Size, typename Type>
	Type&
	vector<Size, Type>::operator [] (int index)
	{
		return _data[index];
	}

	template <int Size, typename Type>
	vector<Size, Type>
	vector<Size, Type>::operator + (vector<Size, Type> const& other) const
	{
		return vector<Size, Type>(this) += other;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator += (vector<Size, Type> const& other)
	{
		for (int i = 0; i < Size; i++) {
			_data[i] += other[i];
		}

		return *this;
	}

	template <int Size, typename Type>
	vector<Size, Type>
	vector<Size, Type>::operator - (vector<Size, Type> const& other) const
	{
		return vector<Size, Type>(this) -= other;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator -= (vector<Size, Type> const& other)
	{
		for (int i = 0; i < Size; i++) {
			_data[i] -= other[i];
		}

		return *this;
	}

	template <int Size, typename Type>
	vector<3, Type>
	vector<Size, Type>::operator * (vector<3, Type> const& other) const
	{
		return vector<3, Type>(this) *= other;
	}

	template <int Size, typename Type>
	vector<3, Type>&
	vector<Size, Type>::operator *= (vector<3, Type> const& other)
	{
		static_assert(Size == 3, "cross product only available on 3 dimensional vectors");

		Type v0 = _data[1] * other[2] - other[1] * _data[2];
		Type v1 = -_data[0] * other[2] + other[0] * _data[2];
		Type v2 = _data[0] * other[1] - other[0] * _data[1];

		_data[0] = v0;
		_data[1] = v1;
		_data[2] = v2;

		return *this;
	}

	template <int Size, typename Type>
	template <int Columns>
	vector<Columns, Type>
	vector<Size, Type>::operator * (matrix<Size, Columns, Type> const& other) const
	{
		vector<Columns, Type> result;

		for (int i = 0; i < Columns; i++) {
			Type element = 0;

			for (int j = 0; j < Size; j++) {
				element += _data[j] * (&other)[i * Columns + j];
			}

			result[i] = element;
		}

		return result;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator *= (matrix<Size, Size, Type> const& other)
	{
		for (int i = 0; i < Size; i++) {
			Type element = 0;

			for (int j = 0; j < Size; j++) {
				element += _data[j] * (&other)[i * Size + j];
			}

			_data[i] = element;
		}

		return *this;
	}

	template <int Size, typename Type>
	Type
	vector<Size, Type>::operator ^ (vector<Size, Type> const& other) const
	{
		return _data[0] * other[0] + _data[1] * other[1] + _data[2] * other[2];
	}

	template <int Size, typename Type>
	vector<Size, Type>
	vector<Size, Type>::operator % (Type scale) const
	{
		vector<Size, Type> result;

		for (int i = 0; i < Size; i++) {
			result[i] = _data[i] * scale;
		}

		return result;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator %= (Type scale)
	{
		for (int i = 0; i < Size; i++) {
			_data[i] *= scale;
		}

		return *this;
	}

	template <int Size, typename Type>
	vector<Size, Type>
	vector<Size, Type>::operator ! (void) const
	{
		return this % (1.0 / magnitude());
	}

	template <int Size, typename Type>
	Type
	vector<Size, Type>::magnitude (void) const
	{
		Type result = 0;

		for (int i = 0; i < Size; i++) {
			result += _data[i] * _data[i];
		}

		return sqrt(result);
	}

	template <int Size, typename Type>
	typename vector<Size, Type>::iterator
	vector<Size, Type>::begin (void)
	{
		return iterator(this);
	}

	template <int Size, typename Type>
	typename vector<Size, Type>::iterator
	vector<Size, Type>::end (void)
	{
		return iterator(this, -1);
	}

	template <int Size, typename Type>
	Type*
	vector<Size, Type>::operator & (void) const
	{
		return _data;
	}
}
