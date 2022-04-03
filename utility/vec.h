#ifndef _UTILITY_VEC__H_
#define _UTILITY_VEC__H_

#include <stddef.h>

typedef struct Vec {
	double *data;
	size_t len;
	size_t cap;
};

struct Vec vec_new(size_t max_size);

void vec_fill(struct Vec* v, const double values[], size_t n);

double vec_get(const struct Vec* v, size_t idx);

void vec_free(struct Vec *v);

#endif // _UTILITY_VEC__H_
