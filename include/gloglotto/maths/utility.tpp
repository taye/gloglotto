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
		template <int Size, typename Type>
		matrix<Size, Size, Type>
		rotation (angle a, float x, float y, float z)
		{
			static_assert(Size == 3 || Size == 4, "only 3x3 and 4x4 matrices");

			matrix<Size, Size, Type> result;

			float s   = sin(angle_cast<angle::radians>(a));
			float c   = cos(angle_cast<angle::radians>(a));
			float mag = sqrt(x * x + y * y + z * z);

			// return identity matrix if magnitude is 0
			if (mag == 0) {
				return result;
			}

			// normalize the matrix
			x /= mag;
			y /= mag;
			z /= mag;

			float xx = x * x;
			float yy = y * y;
			float zz = z * z;
			float xy = x * y;
			float yz = y * z;
			float zx = z * x;
			float xs = x * s;
			float ys = y * s;
			float zs = z * s;

			float one = 1.0 - c;

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
	}
}
