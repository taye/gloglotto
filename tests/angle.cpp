#include <amirite>
#include <gl>

int
main (int argc, char* argv[])
{
	return amirite("angle", {
		{ "degrees", []{
			auto value = gl::angle::degrees::make(60);

			amisimilar(gl::angle_cast<gl::angle::radians>(value), 1.04719755, 7);
			amisimilar(gl::angle_cast<gl::angle::hours>(value), 2.);
		}},

		{ "radians", []{
			auto value = gl::angle::radians::make(1.04719755);

			amisimilar(gl::angle_cast<gl::angle::degrees>(value), 60., 0);
			amisimilar(gl::angle_cast<gl::angle::hours>(value), 2., 0);
		}},

		{ "hours", []{
			auto value = gl::angle::hours::make(2);

			amisimilar(gl::angle_cast<gl::angle::radians>(value), 1.04719755, 7);
			amisimilar(gl::angle_cast<gl::angle::degrees>(value), 60.);
		}}
	});
}
