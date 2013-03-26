#include <amirite>
#include <gl>

int
main (int argc, char* argv[])
{
	return amirite("matrix", {
		{ "creation", []{
			{
				gl::mat2 m;

				amiequal(m[0][0], 0);
				amiequal(m[1][0], 0);

				amiequal(m[0][1], 0);
				amiequal(m[1][1], 0);
			}

			{
				gl::mat3 m;

				amiequal(m[0][0], 0);
				amiequal(m[1][0], 0);
				amiequal(m[2][0], 0);

				amiequal(m[0][1], 0);
				amiequal(m[1][1], 0);
				amiequal(m[2][1], 0);

				amiequal(m[0][2], 0);
				amiequal(m[1][2], 0);
				amiequal(m[2][2], 0);
			}

			{
				gl::mat4 m;

				amiequal(m[0][0], 0);
				amiequal(m[1][0], 0);
				amiequal(m[2][0], 0);
				amiequal(m[3][0], 0);

				amiequal(m[0][1], 0);
				amiequal(m[1][1], 0);
				amiequal(m[2][1], 0);
				amiequal(m[3][1], 0);

				amiequal(m[0][2], 0);
				amiequal(m[1][2], 0);
				amiequal(m[2][2], 0);
				amiequal(m[3][2], 0);

				amiequal(m[0][3], 0);
				amiequal(m[1][3], 0);
				amiequal(m[2][3], 0);
				amiequal(m[3][3], 0);
			}
		}},

		{ "identity", []{
			{
				gl::mat2 m(1);

				amiequal(m[0][0], 1);
				amiequal(m[1][0], 0);

				amiequal(m[0][1], 0);
				amiequal(m[1][1], 1);
			}

			{
				gl::mat3 m(1);

				amiequal(m[0][0], 1);
				amiequal(m[1][0], 0);
				amiequal(m[2][0], 0);

				amiequal(m[0][1], 0);
				amiequal(m[1][1], 1);
				amiequal(m[2][1], 0);

				amiequal(m[0][2], 0);
				amiequal(m[1][2], 0);
				amiequal(m[2][2], 1);
			}

			{
				gl::mat4 m(1);

				amiequal(m[0][0], 1);
				amiequal(m[1][0], 0);
				amiequal(m[2][0], 0);
				amiequal(m[3][0], 0);

				amiequal(m[0][1], 0);
				amiequal(m[1][1], 1);
				amiequal(m[2][1], 0);
				amiequal(m[3][1], 0);

				amiequal(m[0][2], 0);
				amiequal(m[1][2], 0);
				amiequal(m[2][2], 1);
				amiequal(m[3][2], 0);

				amiequal(m[0][3], 0);
				amiequal(m[1][3], 0);
				amiequal(m[2][3], 0);
				amiequal(m[3][3], 1);
			}
		}},

		{ "access", []{
			gl::mat4 m(1);

			amiequal(m[0][0], m(0, 0));
			amiequal(m[1][1], m(1, 1));
			amiequal(m[2][2], m(2, 2));
			amiequal(m[3][3], m(3, 3));
		}},

		{ "+", []{
			{
				gl::mat2 a = {{1, 2}, {2, 1}};
				gl::mat2 b = {{3, 4}, {4, 3}};
				gl::mat2 c = a + b;

				amiequal(c[0][0], 4);
				amiequal(c[0][1], 6);
				amiequal(c[1][0], 6);
				amiequal(c[1][1], 4);
			}

			{
				gl::mat3 a = {{1,2,3},{3,2,1},{1,2,3}};
				gl::mat3 b = {{6,5,4},{4,5,6},{6,5,4}};
				gl::mat3 c = a + b;

				amiequal(c[0][0], 7);
				amiequal(c[0][1], 7);
				amiequal(c[0][2], 7);

				amiequal(c[1][0], 7);
				amiequal(c[1][1], 7);
				amiequal(c[1][2], 7);

				amiequal(c[2][0], 7);
				amiequal(c[2][1], 7);
				amiequal(c[2][2], 7);
			}

			{
				gl::mat4 a = {{1,2,3,4},{4,3,2,1},{1,2,3,4},{1,2,3,4}};
				gl::mat4 b = {{4,3,2,1},{1,2,3,4},{4,3,2,1},{4,3,2,1}};
				gl::mat4 c = a + b;

				amiequal(c[0][0], 5);
				amiequal(c[0][1], 5);
				amiequal(c[0][2], 5);
				amiequal(c[0][3], 5);

				amiequal(c[1][0], 5);
				amiequal(c[1][1], 5);
				amiequal(c[1][2], 5);
				amiequal(c[1][3], 5);

				amiequal(c[2][0], 5);
				amiequal(c[2][1], 5);
				amiequal(c[2][2], 5);
				amiequal(c[2][3], 5);

				amiequal(c[3][0], 5);
				amiequal(c[3][1], 5);
				amiequal(c[3][2], 5);
				amiequal(c[3][3], 5);
			}
		}},

		{ "-", []{
			{
				gl::mat2 a = {{1, 2}, {2, 1}};
				gl::mat2 b = {{3, 4}, {4, 3}};
				gl::mat2 c = a - b;

				amiequal(c[0][0], -2);
				amiequal(c[1][0], -2);
				amiequal(c[0][1], -2);
				amiequal(c[1][1], -2);
			}

			{
				gl::mat3 a = {{6,5,4},{4,5,6},{6,5,4}};
				gl::mat3 b = {{1,2,3},{3,2,1},{1,2,3}};
				gl::mat3 c = a - b;

				amiequal(c[0][0], 5);
				amiequal(c[0][1], 3);
				amiequal(c[0][2], 1);

				amiequal(c[1][0], 1);
				amiequal(c[1][1], 3);
				amiequal(c[1][2], 5);

				amiequal(c[2][0], 5);
				amiequal(c[2][1], 3);
				amiequal(c[2][2], 1);
			}

			{
				gl::mat4 a = {{1,2,3,4},{4,3,2,1},{1,2,3,4},{1,2,3,4}};
				gl::mat4 b = {{4,3,2,1},{1,2,3,4},{4,3,2,1},{4,3,2,1}};
				gl::mat4 c = a - b;

				amiequal(c[0][0], -3);
				amiequal(c[0][1], -1);
				amiequal(c[0][2],  1);
				amiequal(c[0][3],  3);

				amiequal(c[1][0],  3);
				amiequal(c[1][1],  1);
				amiequal(c[1][2], -1);
				amiequal(c[1][3], -3);

				amiequal(c[2][0], -3);
				amiequal(c[2][1], -1);
				amiequal(c[2][2],  1);
				amiequal(c[2][3],  3);

				amiequal(c[3][0], -3);
				amiequal(c[3][1], -1);
				amiequal(c[3][2],  1);
				amiequal(c[3][3],  3);
			}
		}},

		{ "* (scalar)", []{
			{
				gl::mat2 a = {{1, 2}, {2, 1}};
				gl::mat2 b = a * 2;

				amiequal(b[0][0], 2);
				amiequal(b[1][0], 4);

				amiequal(b[0][1], 4);
				amiequal(b[1][1], 2);
			}

			{
				gl::mat3 a = {{1,2,3},{4,3,4},{3,2,1}};
				gl::mat3 b = a * 2;

				amiequal(b[0][0], 2);
				amiequal(b[0][1], 4);
				amiequal(b[0][2], 6);

				amiequal(b[1][0], 8);
				amiequal(b[1][1], 6);
				amiequal(b[1][2], 8);

				amiequal(b[2][0], 6);
				amiequal(b[2][1], 4);
				amiequal(b[2][2], 2);
			}

			{
				gl::mat4 a = {{1,2,3,4},{4,3,2,1},{1,2,3,4},{4,3,2,1}};
				gl::mat4 b = a * 2;

				amiequal(b[0][0], 2);
				amiequal(b[0][1], 4);
				amiequal(b[0][2], 6);
				amiequal(b[0][3], 8);

				amiequal(b[1][0], 8);
				amiequal(b[1][1], 6);
				amiequal(b[1][2], 4);
				amiequal(b[1][3], 2);

				amiequal(b[2][0], 2);
				amiequal(b[2][1], 4);
				amiequal(b[2][2], 6);
				amiequal(b[2][3], 8);

				amiequal(b[3][0], 8);
				amiequal(b[3][1], 6);
				amiequal(b[3][2], 4);
				amiequal(b[3][3], 2);
			}
		}},

		{ "* (vector)", []{
			{
				gl::mat2 a = {{1, 2}, {2, 1}};
				gl::vec2    b = {5, 5};
				gl::vec2    c = a * b;

				amiequal(c[0], 15);
				amiequal(c[1], 15);
			}

			{
				gl::mat3x4 a = {{1,2,3,4},{1,2,3,4},{1,2,3,4}};
				gl::vec3    b = {1,2,3};
				gl::vec4    c = a * b;

				amiequal(c[0], 6);
				amiequal(c[1], 12);
				amiequal(c[2], 18);
				amiequal(c[3], 24);
			}

			{
				gl::mat4x2 a = {{1,2},{1,2},{1,2},{1,2}};
				gl::vec4    b = {3,2,2,3};
				gl::vec2    c = a * b;

				amiequal(c[0], 10);
				amiequal(c[1], 20);
			}
		}},

		{ "* (matrix)", []{
			{
				gl::mat2 a = {{1,2},{3,4}};
				gl::mat2 b = {{5,6},{7,8}};
				gl::mat2 c = a * b;

				amiequal(c[0][0], 23);
				amiequal(c[0][1], 34);

				amiequal(c[1][0], 31);
				amiequal(c[1][1], 46);
			}

			{
				gl::mat3 a = {{1,3,2},{2,2,1},{3,1,3}};
				gl::mat3 b = {{4,6,4},{5,5,6},{6,4,5}};

				gl::mat3 c = a * b;

				amiequal(c[0][0], 28);
				amiequal(c[1][0], 33);
				amiequal(c[2][0], 29);

				amiequal(c[0][1], 28);
				amiequal(c[1][1], 31);
				amiequal(c[2][1], 31);

				amiequal(c[0][2], 26);
				amiequal(c[1][2], 33);
				amiequal(c[2][2], 31);
			}

			{
				gl::mat4 a = {{1,2,3,4},{4,3,2,1},{1,3,2,4},{2,4,1,3}};
				gl::mat4 b = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
				gl::mat4 c = a * b;

				amiequal(c[0][0], 20);
				amiequal(c[0][1], 33);
				amiequal(c[0][2], 17);
				amiequal(c[0][3], 30);

				amiequal(c[1][0], 20);
				amiequal(c[1][1], 33);
				amiequal(c[1][2], 17);
				amiequal(c[1][3], 30);

				amiequal(c[2][0], 20);
				amiequal(c[2][1], 33);
				amiequal(c[2][2], 17);
				amiequal(c[2][3], 30);

				amiequal(c[3][0], 20);
				amiequal(c[3][1], 33);
				amiequal(c[3][2], 17);
				amiequal(c[3][3], 30);
			}

			{
				gl::mat3x2 a = {{1,2},{3,4},{5,6}};
				gl::mat2x3 b = {{6,5,4},{3,2,1}};
				gl::mat2   c = a * b;

				amiequal(c[0][0], 41);
				amiequal(c[0][1], 56);

				amiequal(c[1][0], 14);
				amiequal(c[1][1], 20);
			}

			{
				gl::mat4x2 a = {{8,7},{6,5},{4,3},{2,1}};
				gl::mat3x4 b = {{1,2,3,4},{5,6,6,5},{4,3,2,1}};
				gl::mat3x2 c = a * b;

				amiequal(c[0][0], 40);
				amiequal(c[0][1], 30);

				amiequal(c[1][0], 110);
				amiequal(c[1][1], 88);

				amiequal(c[2][0], 60);
				amiequal(c[2][1], 50);
			}
		}},

		{ "!", []{
			{
				gl::mat2 a = {{1, 2}, {2, 2}};
				gl::mat2 b = !a;

				amiequal(b[0][0], -1.0);
				amiequal(b[1][0],  1.0);

				amiequal(b[0][1],  1.0);
				amiequal(b[1][1], -0.5);
			}

			{
				gl::mat3 a = {{1,2,2},{2,2,2},{4,2,1}};
				gl::mat3 b = !a;

				amiequal(b[0][0], -1.0);
				amiequal(b[0][1],  1.0);
				amiequal(b[0][2],  0.0);

				amiequal(b[1][0],  3.0);
				amiequal(b[1][1], -3.5);
				amiequal(b[1][2],  1.0);

				amiequal(b[2][0], -2.0);
				amiequal(b[2][1],  3.0);
				amiequal(b[2][2], -1.0);
			}

			{
				gl::mat4 a = {{1,2,2,2},{2,2,1,2},{2,2,2,2},{2,2,2,1}};
				gl::mat4 b = !a;

				amiequal(b[0][0], -1.0);
				amiequal(b[0][1],  0.0);
				amiequal(b[0][2],  1.0);
				amiequal(b[0][3],  0.0);

				amiequal(b[1][0],  1.0);
				amiequal(b[1][1],  1.0);
				amiequal(b[1][2], -2.5);
				amiequal(b[1][3],  1.0);

				amiequal(b[2][0],  0.0);
				amiequal(b[2][1], -1.0);
				amiequal(b[2][2],  1.0);
				amiequal(b[2][3],  0.0);

				amiequal(b[3][0],  0.0);
				amiequal(b[3][1],  0.0);
				amiequal(b[3][2],  1.0);
				amiequal(b[3][3], -1.0);
			}
		}},

		{ "~", []{
			{
				gl::mat2 a = {{1, 2}, {3, 4}};
				gl::mat2 b = ~a;

				amiequal(b[0][0], 1);
				amiequal(b[0][1], 3);

				amiequal(b[1][0], 2);
				amiequal(b[1][1], 4);
			}

			{
				gl::mat3 a = {{1,2,3},{4,5,6},{7,8,9}};
				gl::mat3 b = ~a;

				amiequal(b[0][0], 1);
				amiequal(b[0][1], 4);
				amiequal(b[0][2], 7);

				amiequal(b[1][0], 2);
				amiequal(b[1][1], 5);
				amiequal(b[1][2], 8);

				amiequal(b[2][0], 3);
				amiequal(b[2][1], 6);
				amiequal(b[2][2], 9);
			}

			{
				gl::mat4 a = {{1,2,3,4},{5,6,7,8},{8,7,6,5},{4,3,2,1}};
				gl::mat4 b = ~a;

				amiequal(b[0][0], 1);
				amiequal(b[0][1], 5);
				amiequal(b[0][2], 8);
				amiequal(b[0][3], 4);

				amiequal(b[1][0], 2);
				amiequal(b[1][1], 6);
				amiequal(b[1][2], 7);
				amiequal(b[1][3], 3);

				amiequal(b[2][0], 3);
				amiequal(b[2][1], 7);
				amiequal(b[2][2], 6);
				amiequal(b[2][3], 2);

				amiequal(b[3][0], 4);
				amiequal(b[3][1], 8);
				amiequal(b[3][2], 5);
				amiequal(b[3][3], 1);
			}

			{
				gl::mat2x3 a = {{1, 2, 3}, {4, 5, 6}};
				gl::mat3x2 b = ~a;

				amiequal(b[0][0], 1);
				amiequal(b[0][1], 4);

				amiequal(b[1][0], 2);
				amiequal(b[1][1], 5);

				amiequal(b[2][0], 3);
				amiequal(b[2][1], 6);
			}

			{
				gl::mat3x2 a = {{1, 2}, {3, 4}, {5, 6}};
				gl::mat2x3 b = ~a;

				amiequal(b[0][0], 1);
				amiequal(b[0][1], 3);
				amiequal(b[0][2], 5);

				amiequal(b[1][0], 2);
				amiequal(b[1][1], 4);
				amiequal(b[1][2], 6);
			}

			{
				gl::mat4x2 a = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
				gl::mat2x4 b = ~a;

				amiequal(b[0][0], 1);
				amiequal(b[0][1], 3);
				amiequal(b[0][2], 5);
				amiequal(b[0][3], 7);

				amiequal(b[1][0], 2);
				amiequal(b[1][1], 4);
				amiequal(b[1][2], 6);
				amiequal(b[1][3], 8);
			}
		}},

		{ "foreach", []{
			gl::mat3 a = {{1,2,3},{3,2,1},{2,1,3}};

			int i = 0;
			for (auto column : a) {
				switch (i) {
					case 0:
						amiequal(column[0], 1);
						amiequal(column[1], 2);
						amiequal(column[2], 3);
						break;

					case 1:
						amiequal(column[0], 3);
						amiequal(column[1], 2);
						amiequal(column[2], 1);
						break;

					case 2:
						amiequal(column[0], 2);
						amiequal(column[1], 1);
						amiequal(column[2], 3);
						break;
				}

				i++;
			}
		}}
	});
}
