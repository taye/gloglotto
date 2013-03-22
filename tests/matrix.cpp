#include <amirite>
#include <gl>

int
main (int argc, char* argv[])
{
	return amirite("matrix", {
		{ "creation", []{
			{
				gl::matrix<2> m;

				amiequal(m[0][0], 0);
				amiequal(m[1][0], 0);

				amiequal(m[0][1], 0);
				amiequal(m[1][1], 0);
			}

			{
				gl::matrix<3> m;

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
				gl::matrix<4> m;

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
				gl::matrix<2> m(1);

				amiequal(m[0][0], 1);
				amiequal(m[1][0], 0);

				amiequal(m[0][1], 0);
				amiequal(m[1][1], 1);
			}

			{
				gl::matrix<3> m(1);

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
				gl::matrix<4> m(1);

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

		{ "+", []{
			gl::matrix<2, 2> a = {{1, 2}, {2, 1}};
			gl::matrix<2, 2> b = {{3, 4}, {4, 3}};
			gl::matrix<2, 2> c = a + b;

			ami::truthy(c[0][0] == 4 && c[1][0] == 6 &&
			            c[0][1] == 6 && c[1][1] == 4);
		}},

		{ "-", []{
			gl::matrix<2, 2> a = {{1, 2}, {2, 1}};
			gl::matrix<2, 2> b = {{3, 4}, {4, 3}};
			gl::matrix<2, 2> c = a - b;

			ami::truthy(c[0][0] == -2 && c[1][0] == -2 &&
			            c[0][1] == -2 && c[1][1] == -2);
		}},

		{ "* (scalar)", []{
			gl::matrix<2, 2> a = {{1, 2}, {2, 1}};
			gl::matrix<2, 2> b = a * 2;

			amiequal(b[0][0], 2);
			amiequal(b[1][0], 4);

			amiequal(b[0][1], 4);
			amiequal(b[1][1], 2);
		}},

		{ "* (vector)", []{
			{
				gl::matrix<2, 2> a = {{1, 2}, {2, 1}};
				gl::vector<2>    b = {5, 5};
				gl::vector<2>    c = a * b;

				amiequal(c[0], 15);
				amiequal(c[1], 15);
			}

			{ 
				gl::matrix<3, 4> a = {{1,2,3,4},{1,2,3,4},{1,2,3,4}};
				gl::vector<3>    b = {1,2,3};
				gl::vector<4>    c = a * b;

				amiequal(c[0], 6);
				amiequal(c[1], 12);
				amiequal(c[2], 18);
				amiequal(c[3], 24);
			}
			
			{ 
				gl::matrix<4, 2> a = {{1,2},{1,2},{1,2},{1,2}};
				gl::vector<4>    b = {3,2,2,3};
				gl::vector<2>    c = a * b;

				amiequal(c[0], 10);
				amiequal(c[1], 20);
			}
		}},

		{ "* (matrix)", []{
			{
				gl::matrix<2, 2> a = {{1,2},{3,4}};
				gl::matrix<2, 2> b = {{5,6},{7,8}};

				gl::matrix<2, 2> c = a * b;

				amiequal(c[0][0], 23);
				amiequal(c[0][1], 34);

				amiequal(c[1][0], 31);
				amiequal(c[1][1], 46);
			}

			{
				gl::matrix<3, 3> a = {{1,3,2},{2,2,1},{3,1,3}};
				gl::matrix<3, 3> b = {{4,6,4},{5,5,6},{6,4,5}};

				gl::matrix<3, 3> c = a * b;

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
				gl::matrix<4, 4> a = {{1,2,3,4},{4,3,2,1},{1,3,2,4},{2,4,1,3}};
				gl::matrix<4, 4> b = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};

				gl::matrix<4, 4> c = a * b;

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
				gl::matrix<3, 2> a = {{1,2},{3,4},{5,6}};
				gl::matrix<2, 3> b = {{6,5,4},{3,2,1}};

				gl::matrix<2, 2> c = a * b;

				amiequal(c[0][0], 41);
				amiequal(c[0][1], 56);

				amiequal(c[1][0], 14);
				amiequal(c[1][1], 20);
			}

			{
				gl::matrix<4, 2> a = {{8,7},{6,5},{4,3},{2,1}};
				gl::matrix<3, 4> b = {{1,2,3,4},{5,6,6,5},{4,3,2,1}};

				gl::matrix<3, 2> c = a * b;

				amiequal(c[0][0], 40);
				amiequal(c[0][1], 30);

				amiequal(c[1][0], 110);
				amiequal(c[1][1], 88);

				amiequal(c[2][0], 60);
				amiequal(c[2][1], 50);
			}
		}}
	});
}
