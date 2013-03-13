#include <amirite>
#include <gl>

int
main (int argc, char* argv[])
{
	return amirite("matrix", {
		{ "creation", []{
			{
				gl::matrix<2> m;

				ami::equal(m[0][0], 0);
				ami::equal(m[0][1], 0);

				ami::equal(m[1][0], 0);
				ami::equal(m[1][1], 0);
			}

			{
				gl::matrix<3> m;

				ami::equal(m[0][0], 0);
				ami::equal(m[0][1], 0);
				ami::equal(m[0][2], 0);

				ami::equal(m[1][0], 0);
				ami::equal(m[1][1], 0);
				ami::equal(m[1][2], 0);

				ami::equal(m[2][0], 0);
				ami::equal(m[2][1], 0);
				ami::equal(m[2][2], 0);
			}

			{
				gl::matrix<4> m;

				ami::equal(m[0][0], 0);
				ami::equal(m[0][1], 0);
				ami::equal(m[0][2], 0);
				ami::equal(m[0][3], 0);

				ami::equal(m[1][0], 0);
				ami::equal(m[1][1], 0);
				ami::equal(m[1][2], 0);
				ami::equal(m[1][3], 0);

				ami::equal(m[2][0], 0);
				ami::equal(m[2][1], 0);
				ami::equal(m[2][2], 0);
				ami::equal(m[2][3], 0);

				ami::equal(m[3][0], 0);
				ami::equal(m[3][1], 0);
				ami::equal(m[3][2], 0);
				ami::equal(m[3][3], 0);
			}
		}},

		{ "identity", []{
			{
				gl::matrix<2> m(1);

				ami::equal(m[0][0], 1);
				ami::equal(m[0][1], 0);

				ami::equal(m[1][0], 0);
				ami::equal(m[1][1], 1);
			}

			{
				gl::matrix<3> m(1);

				ami::equal(m[0][0], 1);
				ami::equal(m[0][1], 0);
				ami::equal(m[0][2], 0);

				ami::equal(m[1][0], 0);
				ami::equal(m[1][1], 1);
				ami::equal(m[1][2], 0);

				ami::equal(m[2][0], 0);
				ami::equal(m[2][1], 0);
				ami::equal(m[2][2], 1);
			}

			{
				gl::matrix<4> m(1);

				ami::equal(m[0][0], 1);
				ami::equal(m[0][1], 0);
				ami::equal(m[0][2], 0);
				ami::equal(m[0][3], 0);

				ami::equal(m[1][0], 0);
				ami::equal(m[1][1], 1);
				ami::equal(m[1][2], 0);
				ami::equal(m[1][3], 0);

				ami::equal(m[2][0], 0);
				ami::equal(m[2][1], 0);
				ami::equal(m[2][2], 1);
				ami::equal(m[2][3], 0);

				ami::equal(m[3][0], 0);
				ami::equal(m[3][1], 0);
				ami::equal(m[3][2], 0);
				ami::equal(m[3][3], 1);
			}
		}},

		{ "+", []{
			gl::matrix<2, 2> a = {{1, 2}, {2, 1}};
			gl::matrix<2, 2> b = {{3, 4}, {4, 3}};
			gl::matrix<2, 2> c = a + b;

			ami::truthy(c[0][0] == 4 && c[0][1] == 6 &&
			            c[1][0] == 6 && c[1][1] == 4);
		}},

		{ "-", []{
			gl::matrix<2, 2> a = {{1, 2}, {2, 1}};
			gl::matrix<2, 2> b = {{3, 4}, {4, 3}};
			gl::matrix<2, 2> c = a - b;

			ami::truthy(c[0][0] == -2 && c[0][1] == -2 &&
			            c[1][0] == -2 && c[1][1] == -2);
		}},

		{ "* (scalar)", []{
			gl::matrix<2, 2> a = {{1, 2}, {2, 1}};
			gl::matrix<2, 2> b = a * 2;

			ami::equal(b[0][0], 2);
			ami::equal(b[0][1], 4);

			ami::equal(b[1][0], 4);
			ami::equal(b[1][1], 2);
		}},

		{ "* (vector)", []{
			gl::matrix<2, 2> a = {{1, 2}, {2, 1}};
			gl::vector<2>    b = {5, 5};
			gl::vector<2>    c = a * b;

			ami::equal(c[0], 15);
			ami::equal(c[1], 15);
		}},

		{ "* (matrix)", []{
			gl::matrix<3, 3> a = {{1,2,3},{3,2,1},{2,1,3}};
			gl::matrix<3, 3> b = {{4,5,6},{6,5,4},{4,6,5}};
			gl::matrix<3, 3> c = a * b;

			ami::equal(c[0][0], 28);
			ami::equal(c[0][1], 33);
			ami::equal(c[0][2], 29);

			ami::equal(c[1][0], 28);
			ami::equal(c[1][1], 31);
			ami::equal(c[1][2], 31);

			ami::equal(c[2][0], 26);
			ami::equal(c[2][1], 33);
			ami::equal(c[2][2], 31);
		}}
	});
}
