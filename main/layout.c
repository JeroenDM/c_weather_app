#include <stdio.h>
#include <string.h>

#include "layout.h"

enum WidgetType str_to_type(char str[])
{
	for (size_t i = 0; i <= widget_type_max_int; ++i) {
		if (strlen(str) == widget_type_desc_len[i] &&
		    strcmp(str, widget_type_desc[i]) == 0) {
			return (enum WidgetType)i;
		}
	}
	printf("ERROR: unkown widget type %s.\n", str);
	exit(1);
}

char *type_to_str(enum WidgetType type)
{
	if (type <= widget_type_max_int) {
		return widget_type_desc[type];
	}
	printf("ERROR: unkown widget type %i.\n", type);
	exit(1);
}

struct Widget parse_line(char *line)
{
	char buffer[100];
	struct Widget w;
	// clang-format off
    sscanf(
        line,
        "%99s %i %i %i %i %i %i %i",
        buffer,
        &w.color.r,
        &w.color.g,
        &w.color.b,
        &w.rect.x,
        &w.rect.y,
        &w.rect.dx,
        &w.rect.dy
    );
	// clang-format on
	w.type = str_to_type(buffer);
	return w;
}
