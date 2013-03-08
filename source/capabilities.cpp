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

#include <gloglotto/capabilities>

namespace gloglotto
{
	bool
	enabled (unsigned capability) throw (invalid_enum)
	{
		bool result;

		check_exception {
			result = glIsEnabled(capability);
		}

		return result;
	}

	bool
	enabled (unsigned capability, unsigned index) throw (invalid_enum)
	{
		bool result;

		check_exception {
			result = glIsEnabledi(capability, index);
		}

		return result;
	}

	void
	enable (unsigned capability) throw (invalid_enum)
	{
		check_exception {
			glEnable(capability);
		}
	}

	void
	enable (unsigned capability, unsigned index) throw (invalid_enum)
	{
		check_exception {
			glEnablei(capability, index);
		}
	}

	void
	disable (unsigned capability) throw (invalid_enum)
	{
		check_exception {
			glDisable(capability);
		}
	}

	void
	disable (unsigned capability, unsigned index) throw (invalid_enum)
	{
		check_exception {
			glDisablei(capability, index);
		}
	}
}
