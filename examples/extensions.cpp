#include <iostream>
#include <gl>

int
main (int argc, char* argv[])
{
	gl::window::create(&argc, argv, { 800, 600 }, "glblblgbllgblglbl");

	for (auto name : gl::extension::list()) {
		std::cout << name << std::endl;
	}
}
