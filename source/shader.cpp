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

#include <gloglotto/shader_manager>
#include <gloglotto/math>
#include <gloglotto/thin>

namespace gloglotto
{
	shader::~shader (void)
	{
		if (_id != 0) {
			thin::program::destroy(_id);
		}

		delete static_cast<std::function<void()>*>(_function);
	}

	void
	shader::end (void)
	{
		thin::program::use(0);
	}

	void
	shader::uniform (std::string name, float data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, int data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, unsigned int data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, bool data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<1, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<2, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<3, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<4, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<1, int> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<2, int> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<3, int> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<4, int> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<1, unsigned int> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<2, unsigned int> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<3, unsigned int> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<4, unsigned int> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<1, bool> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<2, bool> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<3, bool> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, vector<4, bool> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, matrix<2, 2, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, matrix<3, 3, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, matrix<4, 4, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, matrix<2, 3, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, matrix<3, 2, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, matrix<2, 4, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, matrix<4, 2, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, matrix<3, 4, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	void
	shader::uniform (std::string name, matrix<4, 3, float> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}
}
