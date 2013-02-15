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
		matrix<4, 4>
		perspective (angle fov, float aspect, std::pair<float, float> z)
		{
			matrix<4, 4> result;

			float max_y = z.first * tan(angle_cast<angle::radians>(fov) * 0.5);
			float min_y = -max_y;

			float min_x = min_y * aspect;
			float max_x = -min_x;

			(&result)[0]  = (2.0 * z.first) / (max_x - min_x);
			(&result)[5]  = (2.0 * z.second) / (max_y - min_y);
			(&result)[2]  = (max_x + min_x) / (max_x - min_x);
			(&result)[6]  = (max_y + min_y) / (max_y - min_y);
			(&result)[10] = -((z.second + z.first) / (z.second - z.first));
			(&result)[14] = -1.0;
			(&result)[11] = -((2.0 * (z.second * z.first)) / (z.second - z.first));
			(&result)[15] = 0.0;

			return result;
		}

		matrix<4, 4>
		orthographic (std::pair<float, float> x, std::pair<float, float> y, std::pair<float, float> z)
		{
			matrix<4, 4> result;

			(&result)[0]  = 2.0 / (x.second - x.first);
			(&result)[5]  = 2.0 / (y.second - y.first);
			(&result)[10] = -2.0 / (z.second - z.first);
			(&result)[3]  = -((x.second + x.first) / (x.second - x.first));
			(&result)[7]  = -((y.second + y.first) / (y.second - y.first));
			(&result)[11] = -((z.second + z.first) / (z.second - z.first));
			(&result)[15] = 1.0;

			return result;
		}
	}
}
