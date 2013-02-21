#include <gloglotto/math>
#include <iostream>

using namespace gloglotto;

int
main (int argc, char* argv[])
{
	vector<3, double>    a = { 1, 2, 3 };
	matrix<3, 3, double> b = make::rotation(angle::degrees::make(45), 1.0, 1.0, 1.0);

	a *= b;

	std::cout << "a:";
	for (auto value : a) {
		std::cout << " " << value;
	}
	std::cout << std::endl;

	std::cout << "b:";
	for (auto vec : b) {
		std::cout << " {";
		for (auto value : vec) {
			std::cout << " " << value;
		}
		std::cout << " }";
	}
	std::cout << std::endl;

	return 0;
}
