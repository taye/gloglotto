#include <amirite>
#include <gl>

int
main (int argc, char* argv[])
{
	return amirite("rg", {
		{ "size", []{
			gl::image::format::rg<8> colors(2);

			amiequal(colors.size(), 2);
			amiequal(colors.byte_size(), 4);
		}},

		{ "access", []{
			gl::image::format::rg<8> colors(2);

			colors[0]->r = 1;
			colors[0]->g = 2;

			amiequal(colors[0]->r, 1);
			amiequal(colors[0]->g, 2);
		}},

		{ "foreach", []{
			gl::image::format::rg<8> colors(2);

			colors[0]->r = 1;
			colors[0]->g = 2;

			int i = 0;
			for (auto color : colors) {
				switch (i) {
					case 0:
						amiequal(color->r, 1);
						amiequal(color->g, 2);
						break;

					case 1:
						amiequal(color->r, 0);
						amiequal(color->g, 0);
						break;
				}

				i++;
			}
		}}
	});
}
