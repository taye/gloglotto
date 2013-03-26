#include <amirite>
#include <gl>

int
main (int argc, char* argv[])
{
	return amirite("r", {
		{ "size", []{
			gl::image::format::r<8> colors(2);

			amiequal(colors.size(), 2);
			amiequal(colors.byte_size(), 2);
		}},

		{ "access", []{
			gl::image::format::r<8> colors(2);

			colors[0]->r = 1;

			amiequal(colors[0]->r, 1);
		}},

		{ "foreach", []{
			gl::image::format::r<8> colors(2);

			colors[0]->r = 1;

			int i = 0;
			for (auto color : colors) {
				switch (i) {
					case 0:
						amiequal(color->r, 1);
						break;

					case 1:
						amiequal(color->r, 0);
						break;
				}

				i++;
			}
		}}
	});
}
