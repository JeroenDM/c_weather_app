#ifndef _TERM_DRAWING_H_
#define _TERM_DRAWING_H_

#include <stdio.h>
#include <assert.h>

#define TERM_WIDTH 20
#define TERM_HEIGHT 40
static char canvas[TERM_WIDTH][TERM_HEIGHT];

void term_clear_canvas()
{
	for (size_t x = 0; x < TERM_WIDTH; ++x) {
		for (size_t y = 0; y < TERM_HEIGHT; ++y) {
			canvas[x][y] = ' ';
		}
	}
}

void term_draw_canvas()
{
	for (size_t x = 0; x < TERM_WIDTH; ++x) {
		for (size_t y = 0; y < TERM_HEIGHT; ++y) {
			putchar(canvas[x][y]);
		}
		putchar('\n');
	}
}

void term_draw_pt(size_t x, size_t y)
{
	canvas[x][y] = '*';
}

void term_draw_line(int x0, int y0, int x1, int y1)
{
	assert(x0 <= x1);
	unsigned int dx = x1 - x0;
	unsigned int dy = abs(y1 - y0);
	int y_sign = (y0 <= y1) ? 1 : -1;

	if (dy < dx) {
		dy = (__UINT32_MAX__ + 1.0) * dy / dx;

		for (unsigned int x = 0, y = 0, a = dy / 2; x != dx; ++x) {
			term_draw_pt(x + x0, y_sign * y + y0);
			a += dy;
			y += (unsigned int)(a < dy);
		}
	} else if (dy == dx) {
		for (unsigned x = 0, y = 0; x < dx; ++x) {
			term_draw_pt(x + x0, y_sign * y + y0);
			y++;
		}
	} else {
		dx = (__UINT32_MAX__ + 1.0) * dx / dy;

		for (unsigned int y = 0, x = 0, a = dx / 2; y != dy; ++y) {
			term_draw_pt(x + x0, y_sign * y + y0);
			a += dx;
			x += (unsigned int)(a < dx);
		}
	}
}

#endif // _TERM_DRAWING_H_
