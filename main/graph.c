#include <stdio.h>
#include <assert.h>

#include "graph.h"

#include "utility/vec.h"
#include "utility/assert_macros.h"

void graph_free(struct Graph* g)
{
	NOT_NULL(g);
	vec_free(&g->x_pts);
	vec_free(&g->y_pts);
}

struct Graph graph_new(size_t axis_width, size_t axis_height)
{
	const size_t num_pts = 6;
	double x[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0 };
	double y[] = { 0.2, 0.8, 0.5, 0.4, 0.8, 1.0 };
	struct Graph g;
	g.x_pts = vec_new(num_pts);
	g.y_pts = vec_new(num_pts);
	g.x_pts.len = num_pts;
	g.y_pts.len = num_pts;
	vec_fill(&g.x_pts, x, num_pts);
	vec_fill(&g.y_pts, y, num_pts);
    g.axis_width = axis_width;
    g.axis_height = axis_height;
	return g;
}

void draw_graph(struct Graph g, void (*draw_line)(int,int,int,int))
{
	const size_t num_pts = g.x_pts.len;
	assert(num_pts == g.y_pts.len);
	const double x_scale = g.axis_width;
	const double y_scale = g.axis_height;

	for (size_t i = 0; i < num_pts - 1; ++i) {
        draw_line(
		    (int) (vec_get(&g.x_pts, i) * x_scale),
		    (int) (vec_get(&g.y_pts, i) * y_scale),
		    (int) (vec_get(&g.x_pts, i + 1) * x_scale),
		    (int) (vec_get(&g.y_pts, i + 1) * y_scale)
		);
	}
}