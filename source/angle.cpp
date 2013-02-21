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
	angle::angle (double value)
	{
		_degrees = value;
	}

	angle
	angle::degrees::make (double value)
	{
		return value;
	}

	angle
	angle::radians::make (double value)
	{
		return value * (180 / M_PI);
	}

	angle
	angle::hours::make (double value)
	{
		return value * (1.0 / 15.0);
	}

	namespace angle_operators
	{
		angle
		operator "" _degrees (unsigned long long literal)
		{
			return angle::degrees::make(literal);
		}

		angle
		operator "" _degrees (long double literal)
		{
			return angle::degrees::make(literal);
		}

		angle
		operator "" _degree (unsigned long long literal)
		{
			return angle::degrees::make(literal);
		}

		angle
		operator "" _degree (long double literal)
		{
			return angle::degrees::make(literal);
		}

		angle
		operator "" _radians (unsigned long long literal)
		{
			return angle::radians::make(literal);
		}

		angle
		operator "" _radians (long double literal)
		{
			return angle::radians::make(literal);
		}

		angle
		operator "" _radian (unsigned long long literal)
		{
			return angle::radians::make(literal);
		}

		angle
		operator "" _radian (long double literal)
		{
			return angle::radians::make(literal);
		}

		angle
		operator "" _hours (unsigned long long literal)
		{
			return angle::hours::make(literal);
		}

		angle
		operator "" _hours (long double literal)
		{
			return angle::hours::make(literal);
		}

		angle
		operator "" _hour (unsigned long long literal)
		{
			return angle::hours::make(literal);
		}

		angle
		operator "" _hour (long double literal)
		{
			return angle::hours::make(literal);
		}
	}
}
