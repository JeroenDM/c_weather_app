#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include <stdio.h>
#include <string.h>

enum WidgetType {
	TEXT_INPUT,
	LABEL,
	PLOT,
};

static const size_t widget_type_max_int = (size_t)PLOT;
static const char* widget_type_desc[] = { "text_input", "label", "plot" };
static const size_t widget_type_desc_len[] = { 10, 5, 4 };

struct Color {
	int r, g, b;
};

struct Rect {
	int x, y, dx, dy;
};

struct Widget {
	enum WidgetType type;
	struct Color color;
	struct Rect rect;
};

enum WidgetType str_to_type(char str[]);

char *type_to_str(enum WidgetType type);

struct Widget parse_line(char *line);

#endif
