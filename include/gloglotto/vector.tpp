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
		_data  = new Type[Size];
		std::fill(_data, _data + Size, 0);

		own();
	}

	template <int Size, typename Type>
	vector<Size, Type>::vector (vector<Size, Type> const& from)
	{
		_data = new Type[Size];
		std::copy(&from, &from + Size, _data);

		own();
	}

	template <int Size, typename Type>
	vector<Size, Type>::vector (vector<Size, Type>&& from)
	{
		_data = from._data;

		if (from.owner()) {
			from.disown();
			own();
		}
		else {
			disown();
		}
	}

	template <int Size, typename Type>
	vector<Size, Type>::vector (std::initializer_list<Type> list) throw (std::invalid_argument)
	{
		_data = new Type[Size];

		try {
			*this = list;
		}
		catch (std::invalid_argument& e) {
			delete[] _data;

			throw e;
		}

		own();
	}

	template <int Size, typename Type>
	vector<Size, Type>::vector (Type* data)
	{
		_data = data;

		disown();
	}

	template <int Size, typename Type>
	vector<Size, Type>::~vector (void)
	{
		if (owner()) {
			delete _data;
		}
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator = (vector<Size, Type> const& from)
	{
		std::copy(&from, &from + Size, _data);

		return *this;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator = (vector<Size, Type>&& from)
	{
		return swap(from);
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator = (const Type* data)
	{
		std::copy(data, data + Size, _data);

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
	bool
	vector<Size, Type>::owner (void) const
	{
		return _owner;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::own (void)
	{
		_owner = true;

		return *this;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::disown (void)
	{
		_owner = false;

		return *this;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::swap (vector<Size, Type>& other)
	{
		auto data  = _data;
		auto owner = _owner;

		_data  = other._data;
		_owner = other._owner;

		other._data  = data;
		other._owner = owner;

		return *this;
	}

	template <int Size, typename Type>
	Type const&
	vector<Size, Type>::operator [] (int index) const throw (std::out_of_range)
	{
		if (index < 0 || index >= Size) {
			throw std::out_of_range("index out of range");
		}

		return _data[index];
	}

	template <int Size, typename Type>
	typename vector<Size, Type>::const_iterator
	vector<Size, Type>::begin (void) const
	{
		return const_iterator(this);
	}

	template <int Size, typename Type>
	typename vector<Size, Type>::const_iterator
	vector<Size, Type>::end (void) const
	{
		return const_iterator(this, -1);
	}

	template <int Size, typename Type>
	Type&
	vector<Size, Type>::operator [] (int index) throw (std::out_of_range)
	{
		if (index < 0 || index >= Size) {
			throw std::out_of_range("index out of range");
		}

		return _data[index];
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
	vector<Size, Type>
	vector<Size, Type>::operator + (vector<Size, Type> const& other) const
	{
		return vector<Size, Type>(*this) += other;
	}

	template <int Size, typename Type>
	vector<Size, Type>&&
	vector<Size, Type>::operator + (vector<Size, Type>&& other) const
	{
		other += this;

		return other;
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
		return vector<Size, Type>(*this) -= other;
	}

	template <int Size, typename Type>
	vector<Size, Type>&&
	vector<Size, Type>::operator - (vector<Size, Type>&& other) const
	{
		other -= this;

		return other;
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
		return vector<3, Type>(*this) *= other;
	}

	template <int Size, typename Type>
	vector<3, Type>&&
	vector<Size, Type>::operator * (vector<3, Type>&& other) const
	{
		static_assert(Size == 3, "cross product only available on 3 dimensional vectors");

		Type v0 =  _data[1] * other[2] - other[1] * _data[2];
		Type v1 = -_data[0] * other[2] + other[0] * _data[2];
		Type v2 =  _data[0] * other[1] - other[0] * _data[1];

		other[0] = v0;
		other[1] = v1;
		other[2] = v2;

		return other;
	}

	template <int Size, typename Type>
	vector<3, Type>&
	vector<Size, Type>::operator *= (vector<3, Type> const& other)
	{
		static_assert(Size == 3, "cross product only available on 3 dimensional vectors");

		Type v0 =  _data[1] * other[2] - other[1] * _data[2];
		Type v1 = -_data[0] * other[2] + other[0] * _data[2];
		Type v2 =  _data[0] * other[1] - other[0] * _data[1];

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

		for (int column = 0; column < Columns; column++) {
			Type element = 0;

			for (int row = 0; row < Size; row++) {
				element += _data[row] * (&other)[row * Columns + column];
			}

			result[column] = element;
		}

		return result;
	}

	template <int Size, typename Type>
	vector<Size, Type>&
	vector<Size, Type>::operator *= (matrix<Size, Size, Type> const& other)
	{
		for (int column = 0; column < Size; column++) {
			Type element = 0;

			for (int row = 0; row < Size; row++) {
				element += _data[row] * (&other)[row * Size + column];
			}

			_data[column] = element;
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
	Type*
	vector<Size, Type>::operator & (void)
	{
		return _data;
	}

	template <int Size, typename Type>
	Type const*
	vector<Size, Type>::operator & (void) const
	{
		return _data;
	}

	namespace make
	{
		template <typename Type>
		vector<4, Type>
		plane_equation (vector<3, Type> const& a, vector<3, Type> const& b, vector<3, Type> const& c)
		{
			vector<3, Type> v1;
			vector<3, Type> v2;

			v1[0] = c[0] - a[0];
			v1[1] = c[1] - a[1];
			v1[2] = c[2] - a[2];

			v2[0] = b[0] - a[0];
			v2[1] = b[1] - a[1];
			v2[2] = b[2] - a[2];

			auto tmp = !(v1 * v2);

			return vector<4, Type> { tmp[0], tmp[1], tmp[2],
				-((tmp[0] * c[0]) + (tmp[1] * c[1]) + (tmp[2] * c[2])) };
		}
	}
}
