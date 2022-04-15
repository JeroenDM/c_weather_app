#include "utility/str.h"

#include <string.h>
#include <assert.h>

void test_new_delete()
{
	struct String s = str_new("hello world");
	printf("string: %s\n", s.c_str);
    assert(strcmp(s.c_str, "hello world") == 0);
    str_delete(&s);
}

void test_format()
{
	struct String s = str_format("number=%d\n", 4);
    printf("%s\n", s.c_str);
    assert(strcmp(s.c_str, "number=4"));
}

int main()
{
    test_new_delete();
    test_format();

}
