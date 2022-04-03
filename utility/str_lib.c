#include "str_lib.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

struct String str_new(char content[])
{
	struct String s;
	s.len = strlen(content);
	s.c_str = (char*) malloc(sizeof(char) * strlen(content));
	assert(s.c_str != NULL);
	strcpy(s.c_str, content);
	return s;
}

void str_delete(struct String* s)
{
    free(s->c_str);
    s->c_str = NULL;
    s->len = 0;
}

struct String str_format(char fmt[], ...)
{
    // Obscure implementation based on:
    // https://stackoverflow.com/questions/4867229/code-for-printf-function-in-c
    va_list arg;
    int done;
    char buffer[MAX_FMT_STRING_SIZE];

    va_start(arg, fmt);
    done = vsnprintf(buffer, MAX_FMT_STRING_SIZE, fmt, arg);
    va_end(arg);

    if (done < 0) {
        fprintf(stderr, "failed to format string, error code &d.\n", done);
    }
    else if (done > MAX_FMT_STRING_SIZE) {
        // todo think about null terminator space
        fprintf(
            stdout,
            "warning: format string trunicated by %d characters.\n",
            done - MAX_FMT_STRING_SIZE
        );
    }

    struct String s = str_new(buffer);
    return s;
}
