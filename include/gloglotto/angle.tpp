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

#include <gloglotto/angle>

#include <cmath>

namespace gloglotto
{
	template <>
	inline
	double
	angle_cast<angle::degrees> (angle value)
	{
		return value._radians * (180 / M_PI);
	}

	template <>
	inline
	double
	angle_cast<angle::radians> (angle value)
	{
		return value._radians;
	}

	template <>
	inline
	double
	angle_cast<angle::hours> (angle value)
	{
		return value._radians * (6 / M_PI);
	}
}
