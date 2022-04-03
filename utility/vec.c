#include "vec.h"

#include "assert_macros.h"

struct Vec vec_new(size_t max_size)
{
	struct Vec v;
	v.len = 0;
	v.cap = max_size;
	v.data = (double *)malloc(sizeof(double *) * max_size);
	return v;
}

void vec_fill(struct Vec* v, const double values[], size_t n)
{
	NOT_NULL(v);
	EQUAL(n, v->len);
	memcpy(v->data, values, v->len * sizeof(double));
}

double vec_get(const struct Vec* v, size_t idx)
{
	NOT_NULL(v);
	LESS_THAN(idx, v->len);
	return *(v->data + idx);
}

void vec_free(struct Vec *v)
{
	NOT_NULL(v);
	v->len = 0;
	free(v->data);
}