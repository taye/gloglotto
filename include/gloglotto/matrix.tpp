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
	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>::matrix (Type value) throw (std::logic_error)
	{
		_data = new Type[Columns * Rows];
		std::fill_n(_data, Columns * Rows, 0);

		_vectors = new vector<Rows, Type>*[Columns];
		std::fill_n(_vectors, Columns, nullptr);

		for (int i = 0; i < Rows && i < Columns; i++) {
			_data[i * Rows + i] = value;
		}

		own();
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>::matrix (matrix<Columns, Rows, Type> const& from) : matrix()
	{
		std::copy(&from, &from + Columns * Rows, _data);
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>::matrix (matrix<Columns, Rows, Type>&& from)
	{
		_data    = from._data;
		_vectors = from._vectors;

		from._vectors = nullptr;

		if (from.owner()) {
			from.disown();
			own();
		}
		else {
			disown();
		}
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>::matrix (Type* data)
	{
		_data = data;

		_vectors = new vector<Rows, Type>*[Columns];
		std::fill_n(_vectors, Columns, nullptr);

		disown();
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>::matrix (std::initializer_list<std::initializer_list<Type>> list) throw (std::invalid_argument) : matrix()
	{
		try {
			*this = list;
		}
		catch (std::invalid_argument& e) {
			delete[] _data;

			throw;
		}
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>::~matrix (void)
	{
		if (owner()) {
			delete[] _data;
		}

		if (_vectors) {
			for (int column = 0; column < Columns; column++) {
				if (_vectors[column]) {
					delete _vectors[column];
				}
			}

			delete[] _vectors;
		}
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator = (matrix<Columns, Rows, Type> const& from)
	{
		std::copy(&from, &from + Columns * Rows, _data);

		return *this;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator = (matrix<Columns, Rows, Type>&& from)
	{
		return swap(from);
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator = (const Type* data)
	{
		std::copy(data, data + Columns * Rows, _data);

		return *this;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator = (std::initializer_list<std::initializer_list<Type>> list) throw (std::invalid_argument)
	{
		if (list.size() != Columns) {
			throw std::invalid_argument("number of arguments doesn't match matrix columns");
		}

		int column = 0;
		for (auto list : list) {
			if (list.size() != Rows) {
				throw std::invalid_argument("number of arguments doesn't match matrix rows");
			}

			int row = 0;
			for (auto value : list) {
				_data[column * Rows + row] = value;

				row++;
			}

			column++;
		}

		return *this;
	}

	template <int Columns, int Rows, typename Type>
	bool
	matrix<Columns, Rows, Type>::owner (void) const
	{
		return _owner;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::own (void)
	{
		_owner = true;

		return *this;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::disown (void)
	{
		_owner = false;

		return *this;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::swap (matrix<Columns, Rows, Type>& other)
	{
		auto data    = _data;
		auto owner   = _owner;
		auto vectors = _vectors;

		_data    = other._data;
		_owner   = other._owner;
		_vectors = other._vectors;

		other._data    = data;
		other._owner   = owner;
		other._vectors = vectors;

		return *this;
	}

	template <int Columns, int Rows, typename Type>
	size_t
	matrix<Columns, Rows, Type>::size (void) const
	{
		return Columns;
	}

	template <int Columns, int Rows, typename Type>
	vector<Rows, Type> const&
	matrix<Columns, Rows, Type>::operator [] (int index) const throw (std::out_of_range)
	{
		if (index < 0 || index >= Columns) {
			throw std::out_of_range("index out of range");
		}

		if (!_vectors[index]) {
			_vectors[index] = new vector<Rows, Type>(_data + (index * Rows));
		}

		return *_vectors[index];
	}

	template <int Columns, int Rows, typename Type>
	typename matrix<Columns, Rows, Type>::const_iterator
	matrix<Columns, Rows, Type>::begin (void) const
	{
		return const_iterator(this);
	}

	template <int Columns, int Rows, typename Type>
	typename matrix<Columns, Rows, Type>::const_iterator
	matrix<Columns, Rows, Type>::end (void) const
	{
		return const_iterator(this, -1);
	}

	template <int Columns, int Rows, typename Type>
	vector<Rows, Type>&
	matrix<Columns, Rows, Type>::operator [] (int index) throw (std::out_of_range)
	{
		if (index < 0 || index >= Columns) {
			throw std::out_of_range("index out of range");
		}

		if (!_vectors[index]) {
			_vectors[index] = new vector<Rows, Type>(_data + (index * Rows));
		}

		return *_vectors[index];
	}

	template <int Columns, int Rows, typename Type>
	typename matrix<Columns, Rows, Type>::iterator
	matrix<Columns, Rows, Type>::begin (void)
	{
		return iterator(this);
	}

	template <int Columns, int Rows, typename Type>
	typename matrix<Columns, Rows, Type>::iterator
	matrix<Columns, Rows, Type>::end (void)
	{
		return iterator(this, -1);
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>
	matrix<Columns, Rows, Type>::operator + (matrix<Columns, Rows, Type> const& other) const
	{
		return matrix<Columns, Rows, Type>(*this) += other;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&&
	matrix<Columns, Rows, Type>::operator + (matrix<Columns, Rows, Type>&& other) const
	{
		other += this;

		return other;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator += (matrix<Columns, Rows, Type> const& other)
	{
		for (int i = 0, length = Columns * Rows; i < length; i++) {
				_data[i] += (&other)[i];
		}

		return *this;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>
	matrix<Columns, Rows, Type>::operator - (matrix<Columns, Rows, Type> const& other) const
	{
		return matrix<Columns, Rows, Type>(*this) -= other;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&&
	matrix<Columns, Rows, Type>::operator - (matrix<Columns, Rows, Type>&& other) const
	{
		other -= this;

		return other;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator -= (matrix<Columns, Rows, Type> const& other)
	{
		for (int i = 0, length = Columns * Rows; i < length; i++) {
			_data[i] -= (&other)[i];
		}

		return *this;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>
	matrix<Columns, Rows, Type>::operator * (Type other) const
	{
		return matrix<Columns, Rows, Type>(*this) *= other;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator *= (Type other)
	{
		for (int i = 0, length = Columns * Rows; i < length; i++) {
				_data[i] *= other;
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

		for (int other_column = 0; other_column < OtherColumns; other_column++) {
			for (int row = 0; row < Rows; row++) {
				Type element = 0;

				for (int column = 0; column < Columns; column++) {
					element += _data[column * Rows + row] * (&other)[other_column * Columns + column];
				}

				(&result)[other_column * Rows + row] = element;
			}
		}

		return result;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&&
	matrix<Columns, Rows, Type>::operator * (matrix<Columns, Rows, Type>&& other) const
	{
		for (int other_column = 0; other_column < Columns; other_column++) {
			for (int row = 0; row < Rows; row++) {
				Type element = 0;

				for (int column = 0; column < Columns; column++) {
					element += _data[column * Rows + row] * (&other)[other_column * Columns + column];
				}

				(&other)[other_column * Rows + row] = element;
			}
		}

		return other;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator *= (matrix<Columns, Rows, Type> const& other)
	{
		*this = this * other;

		return *this;
	}

	template <int Columns, int Rows, typename Type>
	vector<Rows, Type>
	matrix<Columns, Rows, Type>::operator * (vector<Columns, Type> const& other) const
	{
		vector<Rows, Type> result;

		for (int row = 0; row < Rows; row++) {
			Type element = 0;

			for (int column = 0; column < Columns; column++) {
				element += _data[column * Rows + row] * (&other)[column];
			}

			result[row] = element;
		}

		return result;
	}

	template <int Columns, int Rows, typename Type>
	vector<Rows, Type>&&
	matrix<Columns, Rows, Type>::operator * (vector<Columns, Type>&& other) const
	{
		static_assert(Columns == Rows, "only square matrices allowed");

		for (int row = 0; row < Rows; row++) {
			Type element = 0;

			for (int column = 0; column < Columns; column++) {
				element += _data[column * Rows + row] * (&other)[column];
			}

			other[row] = element;
		}

		return other;
	}

	template <int Columns, int Rows, typename Type>
	matrix<Columns, Rows, Type>
	matrix<Columns, Rows, Type>::operator ! (void) const throw (std::logic_error)
	{
		static_assert(Columns == Rows, "only square matrices are invertible");

		if (Rows == 2) {
			// |a b|
			// |c d|
			Type a = this[0][0],
					 b = this[1][0],
					 c = this[0][1],
					 d = this[1][1];

			Type det = (a * d) - (b * c);

			if (det == 0) {
				throw std::logic_error("determinant must be non zero");
			}

			return matrix<2, 2, Type> {
				{  d, -b },
				{ -c,  a }
			} * (static_cast<Type>(1) / det);
		}
		else if (Rows == 3) {
			// |a b c|
			// |d e f|
			// |g h k|
			Type a = this[0][0],
					 b = this[1][0],
					 c = this[2][0],
					 d = this[0][1],
					 e = this[1][1],
					 f = this[2][1],
					 g = this[0][2],
					 h = this[1][2],
					 k = this[2][2];

			Type det =
				(a * e * k) - (a * f * h) -
				(b * k * d) + (b * f * g) +
				(c * d * h) - (c * e * g);

			if (det == 0) {
				throw std::logic_error("determinant must be non zero");
			}

			return matrix<3, 3, Type> {
				{ (e * k) - (f * h), (f * g) - (d * k), (d * h) - (e * g) },
				{ (c * h) - (b * k), (a * k) - (c * g), (g * b) - (a * h) },
				{ (b * f) - (c * e), (c * d) - (a * f), (a * e) - (b * d) }
			} * (static_cast<Type>(1) / det);
		}
		else if (Rows == 4) {
			Type a = this[0][0],
					 b = this[1][0],
					 c = this[2][0],
					 d = this[3][0],
					 e = this[0][1],
					 f = this[1][1],
					 g = this[2][1],
					 h = this[3][1],
					 k = this[0][2],
					 l = this[1][2],
					 m = this[2][2],
					 n = this[3][2],
					 o = this[0][3],
					 p = this[1][3],
					 q = this[2][3],
					 r = this[3][3];

			Type det =
				(a * f * m * r) + (a * g * n * p) + (a * h * l * q) +
				(b * e * n * q) + (b * g * k * r) + (b * h * m * o) +
				(c * e * l * r) + (c * f * n * o) + (c * h * k * p) +
				(d * e * m * p) + (d * f * k * q) + (d * g * l * o) -
				(a * f * n * q) - (a * g * l * r) - (a * h * m * p) -
				(b * e * m * r) - (b * g * n * o) - (b * h * k * q) -
				(c * e * n * p) - (c * f * k * r) - (c * h * l * o) -
				(d * e * l * q) - (d * f * m * o) - (d * g * k * p);

			if (det == 0) {
				throw std::logic_error("determinant must be non zero");
			}

			return matrix<4, 4, Type> {
				{ (f * m * r) + (g * n * p) + (h * l * q) - (f * n * q) - (g * l * r) - (h * m * p),
					(e * n * q) + (g * k * r) + (h * m * o) - (e * m * r) - (g * n * o) - (h * k * q),
					(e * l * r) + (f * n * o) + (h * k * p) - (e * n * p) - (f * k * r) - (h * l * o),
					(e * m * p) + (f * k * q) + (g * l * o) - (e * l * q) - (f * m * o) - (g * k * p) },

				{ (b * n * q) + (c * l * r) + (d * m * p) - (b * m * r) - (c * n * p) - (d * l * q),
					(a * m * r) + (c * n * o) + (d * k * q) - (a * n * q) - (c * k * r) - (d * m * o),
					(a * n * p) + (b * k * r) + (d * l * o) - (a * l * r) - (b * n * o) - (d * k * p),
					(a * l * q) + (b * m * o) + (c * k * p) - (a * m * p) - (b * k * q) - (c * l * o) },

				{ (b * g * r) + (c * h * p) + (d * f * q) - (b * h * q) - (c * f * r) - (d * g * p),
					(a * h * q) + (c * e * r) + (d * g * o) - (a * g * r) - (c * h * o) - (d * e * q),
					(a * f * r) + (b * h * o) + (d * e * p) - (a * h * p) - (b * e * r) - (d * f * o),
					(a * g * p) + (b * e * q) + (c * f * o) - (a * f * q) - (b * g * o) - (c * e * p) },

				{ (b * h * m) + (c * f * n) + (d * g * l) - (b * g * n) - (c * h * l) - (d * f * m),
					(a * g * n) + (c * h * k) + (d * e * m) - (a * h * m) - (c * e * n) - (d * g * k),
					(a * h * l) + (b * e * n) + (d * f * k) - (a * f * n) - (b * h * k) - (d * e * l),
					(a * f * m) + (b * g * k) + (c * e * l) - (a * g * l) - (b * e * m) - (c * f * k) }
			} * (static_cast<Type>(1) / det);
		}
	}

	template <int Columns, int Rows, typename Type>
	matrix<Rows, Columns, Type>
	matrix<Columns, Rows, Type>::operator ~ (void) const
	{
		matrix<Rows, Columns, Type> result;

		for (int row = 0; row < Rows; row++) {
			for (int column = 0; column < Columns; column++) {
				(&result)[column * Rows + row] = _data[row * Columns + column];
			}
		}

		return result;
	}

	template <int Columns, int Rows, typename Type>
	Type*
	matrix<Columns, Rows, Type>::operator & (void)
	{
		return _data;
	}

	template <int Columns, int Rows, typename Type>
	Type const*
	matrix<Columns, Rows, Type>::operator & (void) const
	{
		return _data;
	}

	namespace make
	{
		template <typename Type>
		matrix<4, 4, Type>
		perspective (angle fov, Type aspect, std::array<Type, 2> z)
		{
			matrix<4, 4> result(1);

			Type max_y = z[0] * tan(angle_cast<angle::radians>(fov) * 0.5);
			Type min_y = -max_y;

			Type min_x = min_y * aspect;
			Type max_x = -min_x;

			(&result)[0]  =  (2.0 * z[0]) / (max_x - min_x);
			(&result)[5]  =  (2.0 * z[1]) / (max_y - min_y);
			(&result)[2]  =  (max_x + min_x) / (max_x - min_x);
			(&result)[6]  =  (max_y + min_y) / (max_y - min_y);
			(&result)[10] = -((z[1] + z[0]) / (z[1] - z[0]));
			(&result)[14] = -1.0;
			(&result)[11] = -((2.0 * (z[1] * z[0])) / (z[1] - z[0]));
			(&result)[15] =  0.0;

			return result;
		}

		template <typename Type>
		matrix<4, 4, Type>
		orthographic (std::array<Type, 2> x, std::array<Type, 2> y, std::array<Type, 2> z)
		{
			matrix<4, 4> result(1);

			(&result)[0]  =  2.0 / (x[1] - x[0]);
			(&result)[5]  =  2.0 / (y[1] - y[0]);
			(&result)[10] = -2.0 / (z[1] - z[0]);
			(&result)[12] = -((x[1] + x[0]) / (x[1] - x[0]));
			(&result)[13] = -((y[1] + y[0]) / (y[1] - y[0]));
			(&result)[14] = -((z[1] + z[0]) / (z[1] - z[0]));
			(&result)[15] =  1.0;

			return result;
		}

		template <typename Type>
		matrix<4, 4, Type> translation (Type x, Type y, Type z)
		{
			matrix<4, 4, Type> result(1);

			result[3][0] = x;
			result[3][1] = y;
			result[3][2] = z;

			return result;
		}

		template <typename Type>
		matrix<4, 4, Type> translation (vector<3, Type> with)
		{
			return translation<Type>(with[0], with[1], with[2]);
		}

		template <int Size, typename Type>
		matrix<Size, Size, Type>
		rotation (angle x, angle y, angle z)
		{
			static_assert(Size == 3 || Size == 4, "only 3x3 and 4x4 matrices");

			matrix<Size, Size, Type> result(1);

			Type sx = sin(angle_cast<angle::radians>(x));
			Type sy = sin(angle_cast<angle::radians>(y));
			Type sz = sin(angle_cast<angle::radians>(z));

			Type cx = cos(angle_cast<angle::radians>(x));
			Type cy = cos(angle_cast<angle::radians>(y));
			Type cz = cos(angle_cast<angle::radians>(z));

			result[0][0] = (cy * cz);
			result[1][0] = (cx * sz) + (sx * sy * cz);
			result[2][0] = (sx * sz) - (cx * sy * cz);

			result[0][1] = -(cy * sz);
			result[1][1] =  (cx * cz) - (sx * sy * sz);
			result[2][1] =  (sx * cz) + (cx * sy * sz);

			result[0][2] =  sy;
			result[1][2] = -(sx * cy);
			result[2][2] =  (cx * cy);

			return result;
		}

		template <int Size, typename Type>
		matrix<Size, Size, Type>
		rotation (angle a, Type x, Type y, Type z)
		{
			static_assert(Size == 3 || Size == 4, "only 3x3 and 4x4 matrices");

			matrix<Size, Size, Type> result(1);

			Type s   = sin(angle_cast<angle::radians>(a));
			Type c   = cos(angle_cast<angle::radians>(a));
			Type mag = sqrt((x * x) + (y * y) + (z * z));

			// return identity matrix if magnitude is 0
			if (mag == 0) {
				return result;
			}

			// normalize the matrix
			x /= mag;
			y /= mag;
			z /= mag;

			Type one = 1.0 - c;

			result[0][0] = (one * x * x) + c;
			result[1][0] = (one * x * y) - (z * s);
			result[2][0] = (one * z * x) + (y * s);

			result[0][1] = (one * x * y) + (z * s);
			result[1][1] = (one * y * y) + c;
			result[2][1] = (one * y * z) - (x * s);

			result[0][2] = (one * z * x) - (y * s);
			result[1][2] = (one * y * z) + (x * s);
			result[2][2] = (one * z * z) + c;

			return result;
		}

		template <int Size, typename Type>
		matrix<Size, Size, Type>
		rotation (angle a, vector<3, Type> with)
		{
			return rotation<Size, Type>(a, with[0], with[1], with[2]);
		}

		template <int Size, typename Type>
		matrix<Size, Size, Type>
		scale (Type x, Type y, Type z)
		{
			static_assert(Size == 3 || Size == 4, "only 3x3 and 4x4 matrices");

			matrix<Size, Size, Type> result(1);

			result[0][0] = x;
			result[0][1] = y;
			result[0][2] = z;

			return result;
		}

		template <int Size, typename Type>
		matrix<Size, Size, Type>
		scale (vector<3, Type> with)
		{
			return scale<Size, Type>(with[0], with[1], with[2]);
		}

		template <typename Type>
		matrix<4, 4, Type>
		planar_shadow (vector<4, Type> plane, vector<3, Type> light)
		{
			Type a = plane[0];
			Type b = plane[1];
			Type c = plane[2];
			Type d = plane[3];

			Type dx = -light[0];
			Type dy = -light[1];
			Type dz = -light[2];

			matrix<4, 4, Type> result;

			(&result)[0]  = (b * dy) + (c * dz);
			(&result)[1]  = -(a * dy);
			(&result)[1]  = -(a * dz);
			(&result)[3]  =  0.0;

			(&result)[4]  = -(b * dx);
			(&result)[5]  =  (a * dx) + (c * dz);
			(&result)[6]  = -(b * dz);
			(&result)[7]  =  0.0;

			(&result)[8]  = -(c * dx);
			(&result)[9]  = -(c * dy);
			(&result)[10] =  (a * dx) + (b * dy);
			(&result)[11] =  0.0;

			(&result)[12] = -(d * dx);
			(&result)[13] = -(d * dy);
			(&result)[14] = -(d * dz);
			(&result)[15] =  (a * dx) + (b * dy) + (c * dz);

			return result;
		}
	}
}
