#include <cstdio>
#include <cstdlib>

#include <gl>

extern "C" {
	#include "tinytest/tinytest.h"
	#include "tinytest/tinytest_macros.h"
}

void
matrix_empty_test (void* data)
{
	{
		gl::matrix<2> m;

		tt_assert(m[0][0] == 0 && m[0][1] == 0 &&
							m[1][0] == 0 && m[1][1] == 0);
	}

	{
		gl::matrix<3> m(true);

		tt_assert(m[0][0] == 1 && m[0][1] == 0 && m[0][2] == 0 &&
		          m[1][0] == 0 && m[1][1] == 1 && m[1][2] == 0 &&
		          m[2][0] == 0 && m[2][1] == 0 && m[2][2] == 1);
	}

	{
		gl::matrix<4> m(true);

		tt_assert(m[0][0] == 1 && m[0][1] == 0 && m[0][2] == 0 && m[0][3] == 0 &&
		          m[1][0] == 0 && m[1][1] == 1 && m[1][2] == 0 && m[1][3] == 0 &&
		          m[2][0] == 0 && m[2][1] == 0 && m[2][2] == 1 && m[2][3] == 0 &&
		          m[3][0] == 0 && m[3][1] == 0 && m[3][2] == 0 && m[3][3] == 1);
	}



end:;
}

void
matrix_identity_test (void* data)
{
	{
		gl::matrix<2> m(true);

		tt_assert(m[0][0] == 1 && m[0][1] == 0 &&
		          m[1][0] == 0 && m[1][1] == 1);
	}

	{
		gl::matrix<3> m(true);

		tt_assert(m[0][0] == 1 && m[0][1] == 0 && m[0][2] == 0 &&
		          m[1][0] == 0 && m[1][1] == 1 && m[1][2] == 0 &&
		          m[2][0] == 0 && m[2][1] == 0 && m[2][2] == 1);
	}

	{
		gl::matrix<4> m(true);

		tt_assert(m[0][0] == 1 && m[0][1] == 0 && m[0][2] == 0 && m[0][3] == 0 &&
		          m[1][0] == 0 && m[1][1] == 1 && m[1][2] == 0 && m[1][3] == 0 &&
		          m[2][0] == 0 && m[2][1] == 0 && m[2][2] == 1 && m[2][3] == 0 &&
		          m[3][0] == 0 && m[3][1] == 0 && m[3][2] == 0 && m[3][3] == 1);
	}

end:;
}

struct testcase_t creation_tests[] = {
	{ "empty", matrix_empty_test },
	{ "identity", matrix_identity_test },

	END_OF_TESTCASES
};

struct testgroup_t groups[] = {
	{ "creation/", creation_tests },

	END_OF_GROUPS
};

int
main (int argc, char const* argv[])
{
	return tinytest_main(argc, argv, groups);
}
