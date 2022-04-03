#ifndef _STR_LIB_H_
#define _STR_LIB_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "magic.h"

struct String {
	char *c_str;
	unsigned int len;
};

struct String str_new(char content[]);

// Free the memory for a str string.
void str_delete(struct String* s);

struct String str_format(char fmt[], ...);

#endif
