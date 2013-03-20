#include <amirite>
#include <gl>

int
main (int argc, char* argv[])
{
	return amirite("rgba", {
		{ "size", []{
			gl::image::format::rgba<2> colors(2);

			amiequal(colors.size(), 2);
			amiequal(colors.byte_size(), 2);
		}},

		{ "access", []{
			gl::image::format::rgba<2> colors(2);

			colors[0]->r = 1;
			colors[0]->g = 2;
			colors[0]->b = 2;

			amiequal(colors[0]->r, 1);
			amiequal(colors[0]->g, 2);
			amiequal(colors[0]->b, 2);
			amiequal(colors[0]->a, 0);
		}}
	});
}
