#include <gloglotto/math>
#include <iostream>

using namespace gloglotto::math;
using namespace gloglotto::math::angle_operators;

int
main (int argc, char* argv[])
{
	std::cout << "10 hours in degrees: " <<
		angle_cast<angle::degrees>(10_hours) << std::endl;

	std::cout << "1 radian in degrees: " <<
		angle_cast<angle::degrees>(1_radian) << std::endl;

	return 0;
}
