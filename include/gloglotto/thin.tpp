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

#include <gloglotto/utility>
#include <gloglotto/thin>
#include <gloglotto/private>

#include <map>
#include <string>

namespace gloglotto
{
	namespace thin
	{
		namespace window
		{
			namespace callbacks
			{
				extern std::map<std::string, void*> closures;
			}

			template<typename Function, typename... Args>
			void
			callback (std::string name, Function lambda, Args... args) throw (std::invalid_argument)
			{
				using namespace callbacks;

				if (name == "resize") {
					signature_assert<void(int, int)>(lambda);

					glutReshapeFunc(callbacks::resize);
				}
				else if (name == "render") {
					signature_assert<void(void)>(lambda);

					glutDisplayFunc(callbacks::render);
				}
				else if (name == "idle") {
					signature_assert<void(void)>(lambda);

					glutIdleFunc(callbacks::idle);
				}
				else if (name == "visible") {
					signature_assert<void(bool)>(lambda);

					glutVisibilityFunc(callbacks::visible);
				}
				else if (name == "keyboard") {
					signature_assert<void(key, int, int)>(lambda);

					glutKeyboardFunc(callbacks::keyboard);
					glutKeyboardUpFunc(callbacks::keyboard_up);

					glutSpecialFunc(callbacks::special);
					glutSpecialUpFunc(callbacks::special_up);
				}
				else if (name == "mouse.click") {
					signature_assert<void(mouse, int, int)>(lambda);

					glutMouseFunc(callbacks::mouse_click);
				}
				else if (name == "mouse.motion") {
					signature_assert<void(mouse, int, int)>(lambda);

					glutMotionFunc(callbacks::mouse_motion);
					glutPassiveMotionFunc(callbacks::mouse_motion_passive);
				}
				else {
					throw std::invalid_argument("unknown callback");
				}

				if (closures.find(name) != closures.end()) {
					throw std::invalid_argument("the callback already exists");
				}

				closures[name] = new decltype(to_function(lambda))(to_function(lambda));
			}
		}

		namespace program
		{
			namespace uniform
			{
				template <int Size>
				void set (int location, vectors<Size, vector<1, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform1fv(location, Size, &data);
					}
				}

				template <int Size>
				void set (int location, vectors<Size, vector<2, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform2fv(location, Size, &data);
					}
				}

				template <int Size>
				void set (int location, vectors<Size, vector<3, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform3fv(location, Size, &data);
					}
				}

				template <int Size>
				void set (int location, vectors<Size, vector<4, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform4fv(location, Size, &data);
					}
				}

				template <int Size>
				void set (int location, vectors<Size, vector<1, int>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform1iv(location, Size, &data);
					}
				}

				template <int Size>
				void set (int location, vectors<Size, vector<2, int>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform2iv(location, Size, &data);
					}
				}

				template <int Size>
				void set (int location, vectors<Size, vector<3, int>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform3iv(location, Size, &data);
					}
				}

				template <int Size>
				void set (int location, vectors<Size, vector<4, int>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniform4iv(location, Size, &data);
					}
				}

				template <int Size>
				void set (int location, matrices<Size, matrix<2, 2, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix2fv(location, Size, GL_TRUE, &data);
					}
				}

				template <int Size>
				void set (int location, matrices<Size, matrix<3, 3, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix3fv(location, Size, GL_TRUE, &data);
					}
				}

				template <int Size>
				void set (int location, matrices<Size, matrix<4, 4, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix4fv(location, Size, GL_TRUE, &data);
					}
				}

				template <int Size>
				void set (int location, matrices<Size, matrix<2, 3, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix3x2fv(location, Size, GL_TRUE, &data);
					}
				}

				template <int Size>
				void set (int location, matrices<Size, matrix<3, 2, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix2x3fv(location, Size, GL_TRUE, &data);
					}
				}

				template <int Size>
				void set (int location, matrices<Size, matrix<2, 4, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix4x2fv(location, Size, GL_TRUE, &data);
					}
				}

				template <int Size>
				void set (int location, matrices<Size, matrix<4, 2, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix2x4fv(location, Size, GL_TRUE, &data);
					}
				}

				template <int Size>
				void set (int location, matrices<Size, matrix<3, 4, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix4x3fv(location, Size, GL_TRUE, &data);
					}
				}

				template <int Size>
				void set (int location, matrices<Size, matrix<4, 3, float>> data) throw (invalid_operation, invalid_value)
				{
					check_exception {
						glUniformMatrix3x4fv(location, Size, GL_TRUE, &data);
					}
				}
			}
		}
	}
}
