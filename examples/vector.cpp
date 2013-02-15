#include <gloglotto/math>
#include <iostream>

using namespace gloglotto::math;

int
main (int argc, char* argv[])
{
	vector<3, double>    a = { 0.129332729451211, 0.104902414175055, 0.643156466066617 };
	matrix<3, 3, double> b = { { 0.101104050807545, 0.125022056941255, 0.184663664694182 },
	                           { 0.787060787224413, 0.0270290849318147, 0.646034179617113 },
	                           { 0.457340177327373, 0.176341300130546, 0.698730550533084 } };

	a *= b;

	std::cout << "a: " << a[0] << " " << a[1] << " " << a[2] << std::endl;

	return 0;
}
