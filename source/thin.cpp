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
#include <gloglotto/private>

#include <cctype>

namespace gloglotto
{
	namespace thin
	{
		namespace window
		{
			void create (int* argc, char* argv[],
			             std::map<std::string, std::array<int, 2>> attributes,
			             std::string name) throw (std::invalid_argument)
			{
				glutInit(argc, argv);
				glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

				if (attributes.find("size") != attributes.end()) {
					glutInitWindowSize(attributes["size"].at(0), attributes["size"].at(1));
				}

				if (attributes.find("position") != attributes.end()) {
					glutInitWindowPosition(attributes["position"].at(0), attributes["position"].at(1));
				}

				glutCreateWindow(name.c_str());
			}

			void
			loop (void)
			{
				glutMainLoop();
			}

			void
			loop (std::function<void(void)> setup)
			{
				setup();
				loop();
			}

			namespace callbacks
			{
				std::map<std::string, void*> closures;

				template <typename Signature, typename ...Args>
				static inline
				void
				closure (std::string name, Args... args) throw (std::invalid_argument)
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

				void
				idle (void)
				{
					closure<void(void)>("idle");
				}

				void
				visible (int state)
				{
					closure<void(bool)>("visible", state == GLUT_VISIBLE);
				}

				void
				keyboard (unsigned char ch, int x, int y)
				{
					closure<void(key, int, int)>("keyboard", key(ch, glutGetModifiers()), x, y);
				}

				void
				keyboard_up (unsigned char ch, int x, int y)
				{
					closure<void(key, int, int)>("keyboard", key(ch, glutGetModifiers(), true), x, y);
				}

				void
				special (int ch, int x, int y)
				{
					closure<void(key, int, int)>("keyboard", key(ch, glutGetModifiers()), x, y);
				}

				void
				special_up (int ch, int x, int y)
				{
					closure<void(key, int, int)>("keyboard", key(ch, glutGetModifiers(), true), x, y);
				}

				static mouse mouse_current;

				void
				mouse_click (int button, int state, int x, int y)
				{
					if (state == GLUT_DOWN) {
						mouse_current._button    = mouse::cast(button);
						mouse_current._modifiers = glutGetModifiers();
						mouse_current._released  = false;

						closure<void(mouse, int, int)>("mouse.click", mouse_current, x, y);
					}
					else {
						mouse_current._released = true;

						closure<void(mouse, int, int)>("mouse.click", mouse_current, x, y);

						mouse_current._button    = mouse::cast(0);
						mouse_current._modifiers = 0;
					}
				}

				void
				mouse_motion (int x, int y)
				{
					closure<void(mouse, int, int)>("mouse.motion", mouse_current, x, y);
				}

				void
				mouse_motion_passive (int x, int y)
				{
					closure<void(mouse, int, int)>("mouse.motion", mouse(), x, y);
				}
			}

			key::key (unsigned char key, int modifiers, bool released)
			{
				_key       = key;
				_modifiers = modifiers;
				_released  = released;
			}

			key::key (int key, int modifiers, bool released)
			{
				_key       = key << 16;
				_modifiers = modifiers;
				_released  = released;
			}

			key::key (key const& from)
			{
				_key       = from._key;
				_modifiers = from._modifiers;
				_released  = from._released;
			}

			bool
			key::operator == (unsigned char other)
			{
				return _key == other;
			}

			bool
			key::operator == (int other)
			{
				return _key == (other << 16);
			}

			bool
			key::operator == (key const& other)
			{
				return _key == other._key && _modifiers == other._modifiers && _released == other._released;
			}

			bool
			key::operator != (unsigned char other)
			{
				return _key != std::tolower(other);
			}

			bool
			key::operator != (int other)
			{
				return _key != (other << 16);
			}

			bool
			key::operator != (key const& other)
			{
				return _key != other._key || _modifiers != other._modifiers || _released != other._released;
			}

			bool
			key::alt (void)
			{
				return _modifiers & GLUT_ACTIVE_ALT;
			}

			bool
			key::shift (void)
			{
				return _modifiers & GLUT_ACTIVE_SHIFT;
			}

			bool
			key::ctrl (void)
			{
				return _modifiers & GLUT_ACTIVE_CTRL;
			}

			bool
			key::released (void)
			{
				return _released;
			}

			mouse::button
			mouse::cast (int value)
			{
				switch (value) {
					case GLUT_LEFT_BUTTON:
						return button::left;

					case GLUT_MIDDLE_BUTTON:
						return button::middle;

					case GLUT_RIGHT_BUTTON:
						return button::right;
				}

				return button::none;
			}

			mouse::mouse (int modifiers, bool released)
			{
				_button    = button::none;
				_modifiers = modifiers;
				_released  = released;
			}

			mouse::mouse (int button, int modifiers, bool released)
			{
				_button    = cast(button);
				_modifiers = modifiers;
				_released  = released;
			}

			mouse::mouse (mouse const& from)
			{
				*this = from;
			}

			bool
			mouse::alt (void)
			{
				return _modifiers & GLUT_ACTIVE_ALT;
			}

			bool
			mouse::shift (void)
			{
				return _modifiers & GLUT_ACTIVE_SHIFT;
			}

			bool
			mouse::ctrl (void)
			{
				return _modifiers & GLUT_ACTIVE_CTRL;
			}

			bool
			mouse::released (void)
			{
				return _released;
			}
		}

		namespace extensions
		{
			void
			setup (void) throw (exception)
			{
				unsigned int err = glewInit();

				if (err != GLEW_OK) {
					throw exception(reinterpret_cast<const char*>(glewGetErrorString(err)));
				}
			}
		}

		void
		viewport (int width, int height)
		{
			check_exception {
				glViewport(0, 0, width, height);
			}
		}

		void
		viewport (int x, int y, int width, int height)
		{
			check_exception {
				glViewport(x, y, width, height);
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
			clear (enum clear mask) throw (invalid_value, invalid_operation)
			{
				check_exception {
					glClear(static_cast<unsigned int>(mask));
				}
			}

			void
			clear (enum clear mask, float red, float green, float blue, float alpha) throw (invalid_value, invalid_operation)
			{
				unsigned int bitmask = static_cast<unsigned int>(mask);

				if (bitmask & ~(GL_COLOR_BUFFER_BIT | GL_ACCUM_BUFFER_BIT)) {
					throw invalid_value("can only set color and accumulation bits");
				}

				if (bitmask & GL_COLOR_BUFFER_BIT) {
					check_exception {
						glClearColor(red, green, blue, alpha);
					}
				}

				if (bitmask & GL_ACCUM_BUFFER_BIT) {
					check_exception {
						glClearAccum(red, green, blue, alpha);
					}
				}
			}

			void
			clear (enum clear mask, float red, float green, float blue) throw (invalid_value, invalid_operation)
			{
				clear(mask, red, green, blue, 1.0);
			}

			void
			clear (enum clear mask, double depth) throw (invalid_value, invalid_operation)
			{
				unsigned int bitmask = static_cast<unsigned int>(mask);

				if (bitmask & ~GL_DEPTH_BUFFER_BIT) {
					throw invalid_value("can only set depth bits");
				}

				check_exception {
					glClearDepth(depth);
				}
			}

			void
			clear (enum clear mask, float index) throw (invalid_value, invalid_operation)
			{
				unsigned int bitmask = static_cast<unsigned int>(mask);

				if (bitmask & ~GL_COLOR_BUFFER_BIT) {
					throw invalid_value("can only set colors bits");
				}

				check_exception {
					glClearIndex(index);
				}
			}

			void
			clear (enum clear mask, int index) throw (invalid_value, invalid_operation)
			{
				unsigned int bitmask = static_cast<unsigned int>(mask);

				if (bitmask & ~GL_STENCIL_BUFFER_BIT) {
					throw invalid_value("can only set stencil bits");
				}

				check_exception {
					glClearStencil(index);
				}
			}
		}

		namespace program
		{
			namespace shader
			{
				unsigned int
				create (unsigned int value) throw (invalid_enum, invalid_operation)
				{
					unsigned int shader;

					check_exception {
						shader = glCreateShader(value);
					}

					return shader;
				}

				void
				destroy (unsigned int id) throw (invalid_value, invalid_operation)
				{
					check_exception {
						glDeleteShader(id);
					}
				}

				unsigned int
				load (unsigned int id, std::string source) throw (invalid_value, invalid_operation)
				{
					GLchar* string[1] = { (GLchar*) source.c_str() };

					check_exception {
						glShaderSource(id, 1, (const GLchar**) string, NULL);
					}

					return id;
				}

				unsigned int
				compile (unsigned int id) throw (invalid_value, invalid_operation, failed_compilation)
				{
					check_exception {
						glCompileShader(id);
					}

					int status;
					glGetShaderiv(id, GL_COMPILE_STATUS, &status);
					if (status == GL_FALSE) {
						throw failed_compilation("shader compilation failed");
					}

					return id;
				}

				unsigned int
				make (unsigned int value, std::string source) throw (failed_compilation)
				{
					unsigned int shader = create(value);

					load(shader, source);

					try {
						compile(shader);
					}
					catch (const exception& e) {
						destroy(value);

						throw e;
					}

					return shader;
				}

				void
				attach (unsigned int program, unsigned int shader) throw (invalid_value, invalid_operation)
				{
					check_exception {
						glAttachShader(program, shader);
					}
				}

				void
				detach (unsigned int program, unsigned int shader) throw (invalid_value, invalid_operation)
				{
					check_exception {
						glDetachShader(program, shader);
					}
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
				set (int location, vector<1, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform1fv(location, 1, &data);
					}
				}

				void
				set (int location, vector<2, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform2fv(location, 1, &data);
					}
				}

				void
				set (int location, vector<3, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform3fv(location, 1, &data);
					}
				}

				void
				set (int location, vector<4, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform4fv(location, 1, &data);
					}
				}

				void
				set (int location, vector<1, int> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform1iv(location, 1, &data);
					}
				}

				void
				set (int location, vector<2, int> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform2iv(location, 1, &data);
					}
				}

				void
				set (int location, vector<3, int> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform3iv(location, 1, &data);
					}
				}

				void
				set (int location, vector<4, int> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform4iv(location, 1, &data);
					}
				}

				void
				set (int location, matrix<2, 2, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix2fv(location, 1, GL_TRUE, &data);
					}
				}

				void
				set (int location, matrix<3, 3, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix3fv(location, 1, GL_TRUE, &data);
					}
				}

				void
				set (int location, matrix<4, 4, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix4fv(location, 1, GL_TRUE, &data);
					}
				}

				void
				set (int location, matrix<2, 3, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix3x2fv(location, 1, GL_TRUE, &data);
					}
				}

				void
				set (int location, matrix<3, 2, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix2x3fv(location, 1, GL_TRUE, &data);
					}
				}

				void
				set (int location, matrix<2, 4, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix4x2fv(location, 1, GL_TRUE, &data);
					}
				}

				void
				set (int location, matrix<4, 2, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix2x4fv(location, 1, GL_TRUE, &data);
					}
				}

				void
				set (int location, matrix<3, 4, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix4x3fv(location, 1, GL_TRUE, &data);
					}
				}

				void
				set (int location, matrix<4, 3, float> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix3x4fv(location, 1, GL_TRUE, &data);
					}
				}
			}

			unsigned int
			make (std::map<std::string, std::string> source) throw (invalid_operation, failed_linking)
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
			make (std::map<std::string, unsigned int> id) throw (invalid_operation, failed_linking)
			{
				unsigned int program = glCreateProgram();

				for (auto entry : id) {
					shader::attach(program, entry.second);
				}

				try {
					check_exception {
						glLinkProgram(program);
					}

					for (auto entry : id) {
						shader::detach(program, entry.second);
						shader::destroy(entry.second);
					}

					GLint status;
					glGetProgramiv(program, GL_LINK_STATUS, &status);
					if (status == GL_FALSE) {
						throw failed_linking("shader linking failed");
					}
				}
				catch (exception& e) {
					destroy(program);

					throw e;
				}

				return program;
			}

			void
			destroy (unsigned int program)
			{
				check_exception {
					glDeleteProgram(program);
				}
			}

			void
			bind (unsigned int program, unsigned int index, std::string name)
			{
				check_exception {
					glBindAttribLocation(program, index, name.c_str());
				}
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
