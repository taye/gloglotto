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

#include <gloglotto/maths/utility>

namespace gloglotto
{
	namespace math
	{
		namespace make
		{
			template <typename Type>
			matrix<4, 4, Type>
			perspective (angle fov, Type aspect, std::array<Type, 2> z)
			{
				matrix<4, 4> result;

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
				matrix<4, 4> result;

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
				matrix<4, 4, Type> result;

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

				matrix<Size, Size, Type> result;

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

				matrix<Size, Size, Type> result;

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
		}
	}
}
