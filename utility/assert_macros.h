#ifndef _UTILITY_ASSERT_MACROS__H_
#define _UTILITY_ASSERT_MACROS__H_

#include <assert.h>

#define NOT_NULL(x) assert(x != NULL)
#define EQUAL(x, y) assert(x == y)
#define LESS_THAN(x, y) assert(x < y)

#endif // _UTILITY_ASSERT_MACROS__H_
