#ifndef _MAIN_GRAPH__H_
#define _MAIN_GRAPH__H_

#include <stddef.h>

#include "utility/vec.h"

struct Graph {
	struct Vec x_pts;
	struct Vec y_pts;
    size_t axis_width;
    size_t axis_height;
};

void graph_free(struct Graph* g);

struct Graph graph_new();

void draw_graph(struct Graph l, void (*draw_line)(int,int,int,int));

#endif // _UTILITY_VEC__H_
