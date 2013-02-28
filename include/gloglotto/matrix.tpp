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
	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>::matrix (bool identity) throw (std::logic_error)
	{
		if (identity && Rows != Columns) {
			throw std::logic_error("identity matrices must be square");
		}

		_data      = new Type[Columns * Rows];
		_allocated = true;

		std::fill(_data, _data + Columns * Rows, 0);
		std::fill(_vectors, _vectors + Rows, nullptr);

		if (identity) {
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
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>::matrix (matrix<Rows, Columns, Type> const& from)
	{
		_data      = new Type[Columns * Rows];
		_allocated = true;

		std::fill(_vectors, _vectors + Rows, nullptr);
		std::move(&from, &from + Columns * Rows, _data);
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>::matrix (matrix<Rows, Columns, Type>&& from)
	{
		_data = from._data;

		if (from._allocated) {
			from._allocated = false;
			_allocated      = true;
		}
		else {
			_allocated = false;
		}

		std::move(from._vectors, from._vectors + Rows, _vectors);
		std::fill(from._vectors, from._vectors + Rows, nullptr);
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>::matrix (Type* data)
	{
		_data      = data;
		_allocated = false;

		std::fill(_vectors, _vectors + Rows, nullptr);
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>::matrix (std::initializer_list<std::initializer_list<Type>> list) throw (std::invalid_argument)
	{
		_data      = new Type[Columns * Rows];
		_allocated = true;

		std::fill(_vectors, _vectors + Rows, nullptr);

		try {
			*this = list;
		}
		catch (std::invalid_argument& e) {
			delete[] _data;

			throw e;
		}
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>::~matrix (void)
	{
		if (_allocated) {
			delete[] _data;
		}

		for (int row = 0; row < Rows; row++) {
			if (_vectors[row]) {
				delete _vectors[row];
			}
		}
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&
	matrix<Rows, Columns, Type>::operator = (matrix<Rows, Columns, Type> const& from)
	{
		std::move(&from, &from + Columns * Rows, _data);

		return *this;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&
	matrix<Rows, Columns, Type>::operator = (const Type* data)
	{
		std::move(data, data + Columns * Rows, _data);

		return *this;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&
	matrix<Rows, Columns, Type>::operator = (std::initializer_list<std::initializer_list<Type>> list) throw (std::invalid_argument)
	{
		if (list.size() != Rows) {
			throw std::invalid_argument("number of arguments doesn't match matrix rows");
		}

		int row = 0;
		for (auto list : list) {
			if (list.size() != Columns) {
				throw std::invalid_argument("number of arguments doesn't match matrix columns");
			}

			int column = 0;
			for (auto value : list) {
				_data[row * Columns + column] = value;

				column++;
			}

			row++;
		}

		return *this;
	}

	template <int Rows, int Columns, typename Type>
	vector<Columns, Type> const&
	matrix<Rows, Columns, Type>::operator [] (int row) const throw (std::out_of_range)
	{
		if (row < 0 || row >= Rows) {
			throw std::out_of_range("row out of range");
		}

		if (!_vectors[row]) {
			_vectors[row] = new vector<Columns, Type>(_data + (row * Columns));
		}

		return *_vectors[row];
	}

	template <int Rows, int Columns, typename Type>
	typename matrix<Rows, Columns, Type>::const_iterator
	matrix<Rows, Columns, Type>::begin (void) const
	{
		return const_iterator(this);
	}

	template <int Rows, int Columns, typename Type>
	typename matrix<Rows, Columns, Type>::const_iterator
	matrix<Rows, Columns, Type>::end (void) const
	{
		return const_iterator(this, -1);
	}

	template <int Rows, int Columns, typename Type>
	vector<Columns, Type>&
	matrix<Rows, Columns, Type>::operator [] (int row) throw (std::out_of_range)
	{
		if (row < 0 || row >= Rows) {
			throw std::out_of_range("row out of range");
		}

		if (!_vectors[row]) {
			_vectors[row] = new vector<Columns, Type>(_data + (row * Columns));
		}

		return *_vectors[row];
	}

	template <int Rows, int Columns, typename Type>
	typename matrix<Rows, Columns, Type>::iterator
	matrix<Rows, Columns, Type>::begin (void)
	{
		return iterator(this);
	}

	template <int Rows, int Columns, typename Type>
	typename matrix<Rows, Columns, Type>::iterator
	matrix<Rows, Columns, Type>::end (void)
	{
		return iterator(this, -1);
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>
	matrix<Rows, Columns, Type>::operator + (matrix<Rows, Columns, Type> const& other) const
	{
		return matrix<Rows, Columns, Type>(this) += other;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&&
	matrix<Rows, Columns, Type>::operator + (matrix<Rows, Columns, Type>&& other) const
	{
		other += this;

		return other;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&
	matrix<Rows, Columns, Type>::operator += (matrix<Rows, Columns, Type> const& other)
	{
		for (int row = 0; row < Rows; row++) {
			for (int column = 0; column < Columns; column++) {
				_data[row * Columns + column] += (&other)[row * Columns + column];
			}
		}

		return *this;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>
	matrix<Rows, Columns, Type>::operator - (matrix<Rows, Columns, Type> const& other) const
	{
		return matrix<Rows, Columns, Type>(this) -= other;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&&
	matrix<Rows, Columns, Type>::operator - (matrix<Rows, Columns, Type>&& other) const
	{
		other -= this;

		return other;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&
	matrix<Rows, Columns, Type>::operator -= (matrix<Rows, Columns, Type> const& other)
	{
		for (int row = 0; row < Rows; row++) {
			for (int column = 0; column < Columns; column++) {
				_data[row * Columns + column] -= (&other)[row * Columns + column];
			}
		}

		return *this;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>
	matrix<Rows, Columns, Type>::operator * (Type other) const
	{
		return matrix<Rows, Columns, Type>(*this) *= other;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&
	matrix<Rows, Columns, Type>::operator *= (Type other)
	{
		for (int row = 0; row < Rows; row++) {
			for (int column = 0; column < Columns; column++) {
				_data[row * Columns + column] *= other;
			}
		}

		return *this;
	}

	template <int Rows, int Columns, typename Type>
	template <int OtherRows, int OtherColumns>
	matrix<Rows, OtherColumns, Type>
	matrix<Rows, Columns, Type>::operator * (matrix<OtherRows, OtherColumns, Type> const& other) const
	{
		static_assert(Columns == OtherRows, "left column length and right row length must be the same");

		matrix<Rows, OtherColumns, Type> result;

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

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&&
	matrix<Rows, Columns, Type>::operator * (matrix<Rows, Columns, Type>&& other) const
	{
		for (int i = 0; i < Columns; i++) {
			for (int j = 0; j < Rows; j++) {
				Type element = 0;

				for (int h = 0; h < Columns; h++) {
					element += _data[j * Columns + h] * (&other)[j * Columns + i];
				}

				(&other)[j * Columns + i] = element;
			}
		}

		return other;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>&
	matrix<Rows, Columns, Type>::operator *= (matrix<Rows, Columns, Type> const& other)
	{
		*this = this * other;

		return *this;
	}

	template <int Rows, int Columns, typename Type>
	vector<Rows, Type>
	matrix<Rows, Columns, Type>::operator * (vector<Columns, Type> const& other) const
	{
		vector<Rows, Type> result;

		for (int i = 0; i < Rows; i++) {
			Type element = 0;

			for (int j = 0; j < Columns; j++) {
				element += _data[j * Columns + i] * other[j];
			}

			result[i] = element;
		}

		return result;
	}

	template <int Rows, int Columns, typename Type>
	vector<Rows, Type>&&
	matrix<Rows, Columns, Type>::operator * (vector<Columns, Type>&& other) const
	{
		static_assert(Rows == Columns, "only square matrices allowed");

		for (int i = 0; i < Rows; i++) {
			Type element = 0;

			for (int j = 0; j < Columns; j++) {
				element += _data[j * Columns + i] * other[j];
			}

			other[i] = element;
		}

		return other;
	}

	template <int Rows, int Columns, typename Type>
	matrix<Rows, Columns, Type>
	matrix<Rows, Columns, Type>::operator ! (void) const throw (std::logic_error)
	{
		static_assert(Rows == Columns, "only square matrices are invertible");

		if (Rows == 2) {
			// |a b|
			// |c d|
			Type a = this[0][0],
					 b = this[0][1],
					 c = this[1][0],
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
					 b = this[0][1],
					 c = this[0][2],
					 d = this[1][0],
					 e = this[1][1],
					 f = this[1][2],
					 g = this[2][0],
					 h = this[2][1],
					 k = this[2][2];

			Type det =
				(a * e * k) - (a * f * h) -
				(b * k * d) + (b * f * g) +
				(c * d * h) - (c * e * g);

			if (det == 0) {
				throw std::logic_error("determinant must be non zero");
			}

			return matrix<3, 3, Type> {
				{ (e * k) - (f * h), (c * h) - (b * k), (b * f) - (c * e) },
				{ (f * g) - (d * k), (a * k) - (c * g), (c * d) - (a * f) },
				{ (d * h) - (e * g), (g * b) - (a * h), (a * e) - (b * d) }
			} * (static_cast<Type>(1) / det);
		}
		else if (Rows == 4) {
			// |a b c d|
			// |e f g h|
			// |k l m n|
			// |o p q r|
			Type a = this[0][0],
					 b = this[0][1],
					 c = this[0][2],
					 d = this[0][3],
					 e = this[1][0],
					 f = this[1][1],
					 g = this[1][2],
					 h = this[1][3],
					 k = this[2][0],
					 l = this[2][1],
					 m = this[2][2],
					 n = this[2][3],
					 o = this[3][0],
					 p = this[3][1],
					 q = this[3][2],
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
					(b * n * q) + (c * l * r) + (d * m * p) - (b * m * r) - (c * n * p) - (d * l * q),
					(b * g * r) + (c * h * p) + (d * f * q) - (b * h * q) - (c * f * r) - (d * g * p),
					(b * h * m) + (c * f * n) + (d * g * l) - (b * g * n) - (c * h * l) - (d * f * m) },
				{ (e * n * q) + (g * k * r) + (h * m * o) - (e * m * r) - (g * n * o) - (h * k * q),
					(a * m * r) + (c * n * o) + (d * k * q) - (a * n * q) - (c * k * r) - (d * m * o),
					(a * h * q) + (c * e * r) + (d * g * o) - (a * g * r) - (c * h * o) - (d * e * q),
					(a * g * n) + (c * h * k) + (d * e * m) - (a * h * m) - (c * e * n) - (d * g * k) },
				{ (e * l * r) + (f * n * o) + (h * k * p) - (e * n * p) - (f * k * r) - (h * l * o),
					(a * n * p) + (b * k * r) + (d * l * o) - (a * l * r) - (b * n * o) - (d * k * p),
					(a * f * r) + (b * h * o) + (d * e * p) - (a * h * p) - (b * e * r) - (d * f * o),
					(a * h * l) + (b * e * n) + (d * f * k) - (a * f * n) - (b * h * k) - (d * e * l) },
				{ (e * m * p) + (f * k * q) + (g * l * o) - (e * l * q) - (f * m * o) - (g * k * p),
					(a * l * q) + (b * m * o) + (c * k * p) - (a * m * p) - (b * k * q) - (c * l * o),
					(a * g * p) + (b * e * q) + (c * f * o) - (a * f * q) - (b * g * o) - (c * e * p),
					(a * f * m) + (b * g * k) + (c * e * l) - (a * g * l) - (b * e * m) - (c * f * k) }
			} * (static_cast<Type>(1) / det);
		}
	}

	template <int Rows, int Columns, typename Type>
	matrix<Columns, Rows, Type>
	matrix<Rows, Columns, Type>::operator ~ (void) const
	{
		matrix<Columns, Rows, Type> result;

		for (int row = 0; row < Rows; row++) {
			for (int column = 0; column < Columns; column++) {
				(&result)[column * Rows + row] = _data[row * Columns + column];
			}
		}

		return result;
	}

	template <int Rows, int Columns, typename Type>
	Type*
	matrix<Rows, Columns, Type>::operator & (void) const
	{
		return _data;
	}

	namespace make
	{
		template <typename Type>
		matrix<4, 4, Type>
		perspective (angle fov, Type aspect, std::array<Type, 2> z)
		{
			matrix<4, 4> result(true);

			Type max_y = z[0] * tan(angle_cast<angle::radians>(fov) * 0.5);
			Type min_y = -max_y;

			Type min_x = min_y * aspect;
			Type max_x = -min_x;

			(&result)[0]  = (2.0 * z[0]) / (max_x - min_x);
			(&result)[5]  = (2.0 * z[1]) / (max_y - min_y);
			(&result)[2]  = (max_x + min_x) / (max_x - min_x);
			(&result)[6]  = (max_y + min_y) / (max_y - min_y);
			(&result)[10] = -((z[1] + z[0]) / (z[1] - z[0]));
			(&result)[14] = -1.0;
			(&result)[11] = -((2.0 * (z[1] * z[0])) / (z[1] - z[0]));
			(&result)[15] = 0.0;

			return result;
		}

		template <typename Type>
		matrix<4, 4, Type>
		orthographic (std::array<Type, 2> x, std::array<Type, 2> y, std::array<Type, 2> z)
		{
			matrix<4, 4> result(true);

			(&result)[0]  = 2.0 / (x[1] - x[0]);
			(&result)[5]  = 2.0 / (y[1] - y[0]);
			(&result)[10] = -2.0 / (z[1] - z[0]);
			(&result)[3]  = -((x[1] + x[0]) / (x[1] - x[0]));
			(&result)[7]  = -((y[1] + y[0]) / (y[1] - y[0]));
			(&result)[11] = -((z[1] + z[0]) / (z[1] - z[0]));
			(&result)[15] = 1.0;

			return result;
		}

		template <typename Type>
		matrix<4, 4, Type> translation (Type x, Type y, Type z)
		{
			matrix<4, 4, Type> result(true);

			result[0][3] = x;
			result[1][3] = y;
			result[2][3] = z;

			return result;
		}

		template <typename Type>
		matrix<4, 4, Type> translation (vector<3, Type> with)
		{
			return translation<Type>(with[0], with[1], with[2]);
		}

		template <int Size, typename Type>
		matrix<Size, Size, Type>
		rotation (angle a, Type x, Type y, Type z)
		{
			static_assert(Size == 3 || Size == 4, "only 3x3 and 4x4 matrices");

			matrix<Size, Size, Type> result(true);

			Type s   = sin(angle_cast<angle::radians>(a));
			Type c   = cos(angle_cast<angle::radians>(a));
			Type mag = sqrt(x * x + y * y + z * z);

			// return identity matrix if magnitude is 0
			if (mag == 0) {
				return result;
			}

			// normalize the matrix
			x /= mag;
			y /= mag;
			z /= mag;

			Type xx = x * x;
			Type yy = y * y;
			Type zz = z * z;
			Type xy = x * y;
			Type yz = y * z;
			Type zx = z * x;
			Type xs = x * s;
			Type ys = y * s;
			Type zs = z * s;

			Type one = 1.0 - c;

			result[0][0] = one * xx + c;
			result[0][1] = one * xy - zs;
			result[0][2] = one * zx + ys;

			result[1][0] = one * xy + zs;
			result[1][1] = one * yy + c;
			result[1][2] = one * yz - xs;

			result[2][0] = one * zx - ys;
			result[2][1] = one * yz + xs;
			result[2][2] = one * zz + c;

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

			matrix<Size, Size, Type> result(true);

			result[0][0] = x;
			result[1][0] = y;
			result[2][0] = z;

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
			(&result)[4]  = -a * dy;
			(&result)[8]  = -a * dz;
			(&result)[12] = 0.0;

			(&result)[1]  = -b * dx;
			(&result)[5]  = (a * dx) + (c * dz);
			(&result)[9]  = -b * dz;
			(&result)[13] = 0.0;

			(&result)[2]  = -c * dx;
			(&result)[6]  = -c * dy;
			(&result)[10] = (a * dx) + (b * dy);
			(&result)[14] = 0.0;

			(&result)[3]  = -d * dx;
			(&result)[7]  = -d * dy;
			(&result)[11] = -d * dz;
			(&result)[15] = (a * dx) + (b * dy) + (c * dz);

			return result;
		}
	}
}
