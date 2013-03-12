#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE matrix
#include <boost/test/unit_test.hpp>

#include <gl>

BOOST_AUTO_TEST_SUITE(matrix)

BOOST_AUTO_TEST_CASE(creation)
{
	{
		gl::matrix<2> m;

		BOOST_CHECK(m[0][0] == 0 && m[0][1] == 0 &&
		            m[1][0] == 0 && m[1][1] == 0);
	}

	{
		gl::matrix<3> m;

		BOOST_CHECK(m[0][0] == 0 && m[0][1] == 0 && m[0][2] == 0 &&
		            m[1][0] == 0 && m[1][1] == 0 && m[1][2] == 0 &&
		            m[2][0] == 0 && m[2][1] == 0 && m[2][2] == 0);
	}

	{
		gl::matrix<4> m;

		BOOST_CHECK(m[0][0] == 0 && m[0][1] == 0 && m[0][2] == 0 && m[0][3] == 0 &&
		            m[1][0] == 0 && m[1][1] == 0 && m[1][2] == 0 && m[1][3] == 0 &&
		            m[2][0] == 0 && m[2][1] == 0 && m[2][2] == 0 && m[2][3] == 0 &&
		            m[3][0] == 0 && m[3][1] == 0 && m[3][2] == 0 && m[3][3] == 0);
	}
}

BOOST_AUTO_TEST_CASE(identity)
{
	{
		gl::matrix<2> m(1);

		BOOST_CHECK(m[0][0] == 1 && m[0][1] == 0 &&
		            m[1][0] == 0 && m[1][1] == 1);
	}

	{
		gl::matrix<3> m(1);

		BOOST_CHECK(m[0][0] == 1 && m[0][1] == 0 && m[0][2] == 0 &&
		            m[1][0] == 0 && m[1][1] == 1 && m[1][2] == 0 &&
		            m[2][0] == 0 && m[2][1] == 0 && m[2][2] == 1);
	}

	{
		gl::matrix<4> m(1);

		BOOST_CHECK(m[0][0] == 1 && m[0][1] == 0 && m[0][2] == 0 && m[0][3] == 0 &&
		            m[1][0] == 0 && m[1][1] == 1 && m[1][2] == 0 && m[1][3] == 0 &&
		            m[2][0] == 0 && m[2][1] == 0 && m[2][2] == 1 && m[2][3] == 0 &&
		            m[3][0] == 0 && m[3][1] == 0 && m[3][2] == 0 && m[3][3] == 1);
	}
}

BOOST_AUTO_TEST_CASE(sum)
{
	gl::matrix<2, 2> a = {{1, 2}, {2, 1}};
	gl::matrix<2, 2> b = {{3, 4}, {4, 3}};
	gl::matrix<2, 2> c = a + b;

	BOOST_CHECK(c[0][0] == 4 && c[0][1] == 6 &&
	            c[1][0] == 6 && c[1][1] == 4);
}

BOOST_AUTO_TEST_SUITE_END()
