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

#include <gloglotto/shader>
#include <gloglotto/thin>

namespace gloglotto
{
	template <typename Function>
	shader::shader (std::map<std::string, std::string> source, Function lambda)
	{
		_id     = thin::program::make(source);
		_source = source;

		auto function = new decltype(to_function(lambda))(to_function(lambda));

		_signature = &typeid(function);
		_function  = static_cast<void*>(function);
	}

	template <typename ...Args>
	void
	shader::call (Args... args)
	{
		auto function = static_cast<std::function<void(shader&, Args...)>>(_function);

		if (typeid(function) == *_signature) {
			(*function)(*this, args...);
		}
		else {
			throw std::bad_typeid();
		}
	}

	template <int Size>
	void
	shader::uniform (std::string name, std::array<float, Size>data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, std::array<int, Size> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, std::array<unsigned int, Size> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, std::array<bool, Size> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<1, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<2, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<3, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<4, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<1, int>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<2, int>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<3, int>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<4, int>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<1, unsigned int>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<2, unsigned int>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<3, unsigned int>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<4, unsigned int>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<1, bool>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<2, bool>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<3, bool>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, vectors<Size, vector<4, bool>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<2, 2, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<3, 3, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<4, 4, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<2, 3, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<3, 2, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<2, 4, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<4, 2, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<3, 4, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}

	template <int Size>
	void
	shader::uniform (std::string name, matrices<Size, matrix<4, 3, float>> data) throw (invalid_operation, invalid_value)
	{
		thin::program::uniform::set(thin::program::uniform::location(_id, name), data);
	}
}
