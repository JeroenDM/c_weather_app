
#include "main/graph.h"
#include "term_drawing.h"

int main()
{
    term_clear_canvas();
	struct Graph g = graph_new(TERM_WIDTH, TERM_HEIGHT);
	draw_graph(g, term_draw_line);
	term_draw_canvas();
	graph_free(&g);
}
