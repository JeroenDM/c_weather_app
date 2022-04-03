#include <stdio.h>
#include <assert.h>

#include "term_drawing.h"

typedef struct VecTag {
	double *data;
	size_t len;
	size_t cap;
} Vec;

Vec vec_new(size_t max_size)
{
	Vec v;
	v.len = 0;
	v.cap = max_size;
	v.data = (double *)malloc(sizeof(double *) * max_size);
	return v;
}

void vec_free(Vec *v)
{
	v->len = 0;
	free(v->data);
}

struct Graph {
	Vec x_pts;
	Vec y_pts;
    size_t axis_width;
    size_t axis_height;
};

struct Graph line_new()
{
	const size_t num_pts = 6;
	double x[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0 };
	double y[] = { 0.2, 0.8, 0.5, 0.4, 0.8, 1.0 };
	struct Graph l;
	l.x_pts = vec_new(num_pts);
	l.y_pts = vec_new(num_pts);
	l.x_pts.len = num_pts;
	l.y_pts.len = num_pts;
	memcpy(l.x_pts.data, x, l.x_pts.len * sizeof(double));
	memcpy(l.y_pts.data, y, l.y_pts.len * sizeof(double));
    l.axis_width = TERM_WIDTH;
    l.axis_height = TERM_HEIGHT;
	return l;
}

#define array_get(array, idx) *array

void draw_graph(struct Graph l, void (*draw_line)(int,int,int,int))
{
	const size_t num_pts = l.x_pts.len;
	assert(num_pts == l.y_pts.len);
	const double x_scale = l.axis_width;
	const double y_scale = l.axis_height;

	double *x = l.x_pts.data;
	double *y = l.y_pts.data;

	for (size_t i = 0; i < num_pts - 1; ++i) {
        draw_line(
		    (int) (*x * x_scale),
		    (int) (*y * y_scale),
		    (int) (*(x + 1) * x_scale),
		    (int) (*(y + 1) * y_scale)
		);
        y++;
        x++;
	}
}

int main()
{
    term_clear_canvas();
	struct Graph g = line_new();
	draw_graph(g, term_draw_line);
	term_draw_canvas();
}
