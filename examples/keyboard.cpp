#include <iostream>
#include <gl>

int
main (int argc, char* argv[])
{
	gl::window::create(&argc, argv, { 800, 600 }, "glblblgbllgblglbl");
	gl::window::on<gl::window::event::keyboard>([](gl::window::key key, int x, int y) {
		std::cout << key.name() << " (" << x << ", " << y << ")" << std::endl;
	});

	gl::window::loop();

	return 0;
}
