#include <cstdio>
#include <cstdlib>

#include <gl>

extern "C" {
	#include "tinytest/tinytest.h"
	#include "tinytest/tinytest_macros.h"
}

struct testcase_t creation_tests[] = {
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
