#include <iostream>
#include <gl>

int
main (int argc, char* argv[])
{
	gl::window::create(&argc, argv, { 800, 600 }, "Triangle");

	gl::shader_manager shaders;
	shaders.add("identity", {
		{ "vertex", R"(
			attribute vec3 vertex;

			void
			main (void)
			{
				gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0);
			}
		)" },

		{ "fragment", R"(
			uniform vec3 color;

			void
			main (void)
			{
				gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
			}
		)" } },
	[](gl::shader& shader, gl::vector<3> color) {
		shader.uniform("color", color);
	});

	gl::window::on<gl::window::event::keyboard>([](gl::window::key& key, int x, int y) {
		(void) x;
		(void) y;

		if (key == gl::window::key::esc || key == 'q') {
			gl::window::exit();
		}
	});

	gl::window::on<gl::window::event::resize>([](int w, int h) {
		gl::viewport(w, h);
	});

	gl::window::on<gl::window::event::render>([&] {
		static gl::vectors<3, gl::vector<3>> triangle {
			{  0.75,  0.75, 0.0 },
			{  0.75, -0.75, 0.0 },
			{ -0.75, -0.75, 0.0 } };

		static gl::buffer buffer(gl::target::vertex::data, gl::usage::stream::draw, triangle);

		static auto beginning = std::chrono::high_resolution_clock::now();
		       auto now       = std::chrono::high_resolution_clock::now();

		static int last_tick = 0;
		       int tick      = std::chrono::duration_cast<std::chrono::milliseconds>(now - beginning).count();

		if (tick > last_tick) {
			while (tick > last_tick) {
				triangle *= gl::make::rotation(gl::angle::radians::make(0.01), 1.0f, 1.0f, 1.0f);

				last_tick += 1000 / 60.0;
			}

			buffer.replace(gl::target::vertex::data, triangle);
		}

		gl::clear(gl::clear::color | gl::clear::depth | gl::clear::stencil);

		with_shader(shaders, "identity", gl::vector<3> { 1.0, 1.0, 1.0 }) {
			self.attribute<gl::vector<3>>("vertex", buffer);

			self.draw(gl::primitive::triangle, 3);
		}

		gl::window::render();
		gl::window::update();
	});

	gl::window::loop([] {
		gl::clear(gl::clear::color, 0, 0, 0);
	});
}
