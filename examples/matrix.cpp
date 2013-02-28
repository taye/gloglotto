#include <gloglotto/math>
#include <iostream>

using namespace gloglotto;

int
main (int argc, char* argv[])
{
	matrix<2, 2> a = {{1, 2}, {2, 1}};
	matrix<2, 2> b = {{3, 4}, {4, 3}};
	vector<2>    c = {5, 5};

	std::cout << "|1 2|   |3 4|   |" << (a + b)[0][0] << " " << (a + b)[0][1] << "|" << std::endl;
	std::cout << "|   | + |   | = |" << " "           << " " << " "           << "|" << std::endl;
	std::cout << "|2 1|   |4 3|   |" << (a + b)[1][0] << " " << (a + b)[1][1] << "|" << std::endl;

	std::cout << std::endl;

	std::cout << "|1 2|   |3 4|   |" << (a - b)[0][0] << " " << (a - b)[0][1] << "|" << std::endl;
	std::cout << "|   | - |   | = |" << "  "          << " " << "  "          << "|" << std::endl;
	std::cout << "|2 1|   |4 3|   |" << (a - b)[1][0] << " " << (a - b)[1][1] << "|" << std::endl;

	std::cout << std::endl;

	std::cout << "|1 2|       |" << (a * 2)[0][0] << " " << (a * 2)[0][1] << "|" << std::endl;
	std::cout << "|   | * 2 = |" << " "           << " " << " "           << "|" << std::endl;
	std::cout << "|2 1|       |" << (a * 2)[1][0] << " " << (a * 2)[1][1] << "|" << std::endl;

	std::cout << std::endl;

	std::cout << "|1 2|" << std::endl;
	std::cout << "|   | * [5, 5] = [" << (a * c)[0] << ", " << (a * c)[1] << "]" << std::endl;
	std::cout << "|2 1|" << std::endl;

	std::cout << std::endl;

	matrix<3, 3> d = {{1,2,3},{3,2,1},{2,1,3}};
	matrix<3, 3> e = {{4,5,6},{6,5,4},{4,6,5}};

	std::cout << "|1 2 3|   |4 5 6|   |" << (d * e)[0][0] << " " << (d * e)[0][1] << " " << (d * e)[0][2] << "|" << std::endl;
	std::cout << "|3 2 1| * |6 5 4| = |" << (d * e)[1][0] << " " << (d * e)[1][1] << " " << (d * e)[1][2] << "|" << std::endl;
	std::cout << "|2 1 3|   |4 6 5|   |" << (d * e)[2][0] << " " << (d * e)[2][1] << " " << (d * e)[2][2] << "|" << std::endl;

	std::cout << std::endl;

	std::cout << "|1 2 3|T   |" << (~d)[0][0] << " " << (~d)[0][1] << " " << (~d)[0][2] << "|" << std::endl;
	std::cout << "|3 2 1|  = |" << (~d)[1][0] << " " << (~d)[1][1] << " " << (~d)[1][2] << "|" << std::endl;
	std::cout << "|2 1 3|    |" << (~d)[2][0] << " " << (~d)[2][1] << " " << (~d)[2][2] << "|" << std::endl;

	return 0;
}
