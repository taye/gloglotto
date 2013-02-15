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
	template <class Function>
	shader::shader (std::vector<std::string> attrs,
	                                std::map<std::string, std::string> source,
	                                Function lambda)
	{
		_id     = thin::program::make(source);
		_source = source;

		for (size_t i = 0; i < attrs.size(); i++) {
			auto& name = attrs[i];

			_attributes[name] = i;
			thin::program::bind(_id, i, name);
		}

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
}
