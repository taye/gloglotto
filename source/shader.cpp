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

namespace gloglotto
{
	shader::shader (std::multimap<std::string, std::string> source) throw (invalid_operation, failed_compilation, failed_linking)
	{
		_id     = make(source);
		_source = source;

		_function = nullptr;
	}

	unsigned int
	shader::make (std::multimap<std::string, std::string>& source) const throw (failed_compilation, failed_linking, invalid_enum, invalid_operation)
	{
		static std::map<std::string, unsigned int> enums = {
			{ "vertex",   GL_VERTEX_SHADER },
			{ "fragment", GL_FRAGMENT_SHADER },
			{ "geometry", GL_GEOMETRY_SHADER },

			{ "tessellation:evaluation", GL_TESS_EVALUATION_SHADER },
			{ "tessellation:control",    GL_TESS_CONTROL_SHADER }
		};

		unsigned int program = 0;

		check_exception {
			program = glCreateProgram();
		}

		std::vector<unsigned int> shaders;
		try {
			for (auto entry : source) {
				const GLchar* string[1] = { (GLchar*) entry.second.c_str() };
				unsigned int  shader;

				check_exception {
					shader = glCreateShader(enums.at(entry.first));
				}

				glShaderSource(shader, 1, reinterpret_cast<const GLchar**>(&string), NULL);
				glCompileShader(shader);

				int status;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
				if (status == GL_FALSE) {
					int length;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

					std::string log(length, 0);
					glGetShaderInfoLog(shader, length, &length, const_cast<char*>(log.data()));

					throw failed_compilation(log);
				}

				shaders.push_back(shader);
			}
		}
		catch (exception& e) {
			for (auto id : shaders) {
				glDetachShader(_id, id);
				glDeleteShader(id);
			}

			glDeleteProgram(program);

			throw e;
		}

		for (auto shader : shaders) {
			glAttachShader(program, shader);
		}

		glLinkProgram(program);

		for (auto shader : shaders) {
			glDetachShader(program, shader);
			glDeleteShader(shader);
		}

		int status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::string log(length, '\0');
			glGetShaderInfoLog(program, length, &length, const_cast<char*>(log.data()));

			glDeleteProgram(program);

			throw failed_compilation(log);
		}

		return program;
	}

	shader::~shader (void)
	{
		if (_id != 0) {
			glDeleteProgram(_id);
		}

		delete static_cast<std::function<void()>*>(_function);
	}

	void
	shader::end (void)
	{
		glUseProgram(0);
	}

	int
	shader::uniform (std::string name) const throw (invalid_operation)
	{
		int location;

		check_exception {
			location = glGetUniformLocation(_id, name.c_str());
		}

		return location;
	}

	void
	shader::uniform (std::string name, float data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1f(uniform(name), data);
		}
	}

	void
	shader::uniform (std::string name, int data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1i(uniform(name), data);
		}
	}

	void
	shader::uniform (std::string name, unsigned int data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1ui(uniform(name), data);
		}
	}

	void
	shader::uniform (std::string name, bool data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1i(uniform(name), data);
		}
	}

	void
	shader::uniform (std::string name, vector<1, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1fv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<2, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform2fv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<3, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform3fv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<4, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform4fv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<1, int> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1iv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<2, int> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform2iv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<3, int> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform3iv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<4, int> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform4iv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<1, unsigned int> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform1uiv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<2, unsigned int> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform2uiv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<3, unsigned int> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform3uiv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<4, unsigned int> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniform4uiv(uniform(name), 1, &data);
		}
	}

	void
	shader::uniform (std::string name, vector<1, bool> data) throw (invalid_operation, invalid_value)
	{
		int buffer[] = { data[0] };

		check_exception {
			glUniform1iv(uniform(name), 1, buffer);
		}
	}

	void
	shader::uniform (std::string name, vector<2, bool> data) throw (invalid_operation, invalid_value)
	{
		int buffer[] = { data[0], data[1] };

		check_exception {
			glUniform2iv(uniform(name), 1, buffer);
		}
	}

	void
	shader::uniform (std::string name, vector<3, bool> data) throw (invalid_operation, invalid_value)
	{
		int buffer[] = { data[0], data[1], data[2] };

		check_exception {
			glUniform3iv(uniform(name), 1, buffer);
		}
	}

	void
	shader::uniform (std::string name, vector<4, bool> data) throw (invalid_operation, invalid_value)
	{
		int buffer[] = { data[0], data[1], data[2], data[3] };

		check_exception {
			glUniform4iv(uniform(name), 1, buffer);
		}
	}

	void
	shader::uniform (std::string name, matrix<2, 2, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix2fv(uniform(name), 1, GL_TRUE, &data);
		}
	}

	void
	shader::uniform (std::string name, matrix<3, 3, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix3fv(uniform(name), 1, GL_TRUE, &data);
		}
	}

	void
	shader::uniform (std::string name, matrix<4, 4, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix4fv(uniform(name), 1, GL_TRUE, &data);
		}
	}

	void
	shader::uniform (std::string name, matrix<2, 3, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix3x2fv(uniform(name), 1, GL_TRUE, &data);
		}
	}

	void
	shader::uniform (std::string name, matrix<3, 2, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix2x3fv(uniform(name), 1, GL_TRUE, &data);
		}
	}

	void
	shader::uniform (std::string name, matrix<2, 4, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix4x2fv(uniform(name), 1, GL_TRUE, &data);
		}
	}

	void
	shader::uniform (std::string name, matrix<4, 2, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix2x4fv(uniform(name), 1, GL_TRUE, &data);
		}
	}

	void
	shader::uniform (std::string name, matrix<3, 4, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix4x3fv(uniform(name), 1, GL_TRUE, &data);
		}
	}

	void
	shader::uniform (std::string name, matrix<4, 3, float> data) throw (invalid_operation, invalid_value)
	{
		check_exception {
			glUniformMatrix3x4fv(uniform(name), 1, GL_TRUE, &data);
		}
	}
}
