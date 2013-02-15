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

#include <gloglotto/thin>

namespace gloglotto
{
	namespace thin
	{
		namespace window
		{
			void create (int* argc, char* argv[],
			             std::map<std::string, std::vector<int>> attributes,
			             std::string name) throw (std::invalid_argument)
			{
				glutInit(argc, argv);
				glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

				if (attributes.find("size") != attributes.end()) {
					if (attributes["size"].size() != 2) {
						throw std::invalid_argument("size must have two elements");
					}

					glutInitWindowSize(attributes["size"].at(0), attributes["size"].at(1));
				}

				if (attributes.find("position") != attributes.end()) {
					if (attributes["size"].size() != 2) {
						throw std::invalid_argument("size must have two elements");
					}

					glutInitWindowPosition(attributes["position"].at(0), attributes["position"].at(1));
				}

				glutCreateWindow(name.c_str());
			}

			void
			loop (std::function<void(void)> setup)
			{
				setup();
				glutMainLoop();
			}

			namespace callbacks
			{
				std::map<std::string, void*> closures;

				template <typename Signature, typename ...Args>
				static inline
				void
				closure (std::string name, Args... args)
				{
					if (closures.find(name) == closures.end()) {
						throw std::invalid_argument("unknown callback");
					}

					(*static_cast<std::function<Signature>*>(closures[name]))(args...);
				}

				void
				resize (int width, int height)
				{
					closure<void(int, int)>("resize", width, height);
				}

				void
				render (void)
				{
					closure<void(void)>("render");
				}
			}
		}

		namespace extensions
		{
			void
			setup (void) throw (std::runtime_error)
			{
				unsigned int err = glewInit();

				if (err != GLEW_OK) {
					throw std::runtime_error((const char*) glewGetErrorString(err));
				}
			}
		}

		void
		viewport (int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void
		viewport (int x, int y, int width, int height)
		{
			glViewport(x, y, width, height);
		}

		namespace clear
		{
			void
			color (float red, float green, float blue)
			{
				glClearColor(red, green, blue, 1.0);
			}

			void
			color (float red, float green, float blue, float alpha)
			{
				glClearColor(red, green, blue, alpha);
			}
		}

		namespace buffers
		{
			void
			swap (void)
			{
				glutSwapBuffers();
			}

			void
			clear (GLbitfield mask)
			{
				glClear(mask);
			}
		}

		namespace program
		{
			namespace shader
			{
				unsigned int
				create (unsigned int value)
				{
					return glCreateShader(value);
				}

				void
				destroy (unsigned int id)
				{
					glDeleteShader(id);
				}

				unsigned int
				load (unsigned int id, std::string source)
				{
					GLchar* string[1] = { (GLchar*) source.c_str() };

					glShaderSource(id, 1, (const GLchar**) string, NULL);

					return id;
				}

				unsigned int
				compile (unsigned int id)
				{
					glCompileShader(id);

					int status;
					glGetShaderiv(id, GL_COMPILE_STATUS, &status);
					if (status == GL_FALSE) {
						throw std::runtime_error("shader compilation failed");
					}

					return id;
				}

				unsigned int
				make (unsigned int value, std::string source)
				{
					unsigned int shader = create(value);

					load(shader, source);

					try {
						compile(shader);
					}
					catch (const std::runtime_error& e) {
						destroy(value);

						throw e;
					}

					return shader;
				}
			}

			namespace uniform
			{
				int
				location (unsigned int program, std::string name)
				{
					return glGetUniformLocation(program, name.c_str());
				}

				void
				set (int location, math::vector<1, float> data)
				{
					glUniform1fv(location, 1, &data);
				}

				void
				set (int location, math::vector<2, float> data)
				{
					glUniform2fv(location, 1, &data);
				}

				void
				set (int location, math::vector<3, float> data)
				{
					glUniform3fv(location, 1, &data);
				}

				void
				set (int location, math::vector<4, float> data)
				{
					glUniform4fv(location, 1, &data);
				}

				void
				set (int location, math::vector<1, int> data)
				{
					glUniform1iv(location, 1, &data);
				}

				void
				set (int location, math::vector<2, int> data)
				{
					glUniform2iv(location, 1, &data);
				}

				void
				set (int location, math::vector<3, int> data)
				{
					glUniform3iv(location, 1, &data);
				}

				void
				set (int location, math::vector<4, int> data)
				{
					glUniform4iv(location, 1, &data);
				}

				void
				set (int location, math::matrix<2, 2, float> data)
				{
					glUniformMatrix2fv(location, 1, GL_TRUE, &data);
				}

				void
				set (int location, math::matrix<3, 3, float> data)
				{
					glUniformMatrix3fv(location, 1, GL_TRUE, &data);
				}

				void
				set (int location, math::matrix<4, 4, float> data)
				{
					glUniformMatrix4fv(location, 1, GL_TRUE, &data);
				}

				void
				set (int location, math::matrix<2, 3, float> data)
				{
					glUniformMatrix2x3fv(location, 1, GL_TRUE, &data);
				}

				void
				set (int location, math::matrix<3, 2, float> data)
				{
					glUniformMatrix3x2fv(location, 1, GL_TRUE, &data);
				}

				void
				set (int location, math::matrix<2, 4, float> data)
				{
					glUniformMatrix2x4fv(location, 1, GL_TRUE, &data);
				}

				void
				set (int location, math::matrix<4, 2, float> data)
				{
					glUniformMatrix4x2fv(location, 1, GL_TRUE, &data);
				}

				void
				set (int location, math::matrix<3, 4, float> data)
				{
					glUniformMatrix3x4fv(location, 1, GL_TRUE, &data);
				}

				void
				set (int location, math::matrix<4, 3, float> data)
				{
					glUniformMatrix4x3fv(location, 1, GL_TRUE, &data);
				}
			}

			unsigned int
			make (std::map<std::string, std::string> source)
			{
				static std::map<std::string, unsigned int> enums = {
					{ "vertex",   GL_VERTEX_SHADER },
					{ "fragment", GL_FRAGMENT_SHADER },
					{ "geometry", GL_GEOMETRY_SHADER },

					{ "tessellation:evaluation", GL_TESS_EVALUATION_SHADER },
					{ "tessellation:control",    GL_TESS_CONTROL_SHADER }
				};

				std::map<std::string, unsigned int> id;

				for (auto entry : source) {
					id[entry.first] = shader::make(enums[entry.first], entry.second);
				}

				return make(id);
			}

			unsigned int
			make (std::map<std::string, unsigned int> id)
			{
				unsigned int program = glCreateProgram();

				for (auto entry : id) {
					glAttachShader(program, entry.second);
				}

				glLinkProgram(program);

				for (auto entry : id) {
					shader::destroy(entry.second);
				}

				GLint status;
				glGetProgramiv(program, GL_LINK_STATUS, &status);
				if (status == GL_FALSE) {
					destroy(program);

					throw std::runtime_error("shader linking failed");
				}

				return program;
			}

			void
			destroy (unsigned int program)
			{
				glDeleteProgram(program);
			}

			void
			bind (unsigned int program, unsigned int index, std::string name)
			{
				glBindAttribLocation(program, index, name.c_str());
			}
		}

		namespace error
		{
			unsigned int
			code (void)
			{
				return glGetError();
			}

			std::string
			string (unsigned int code)
			{
				const GLubyte* string = gluErrorString(code);

				return std::string(reinterpret_cast<const char*>(string));
			}
		}
	}
}
