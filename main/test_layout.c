#include <stdio.h>

#include "layout.h"

void draw(struct Widget w)
{
	printf("---------------------\n");
	// clang-format off
	printf(
        "type: %s\nrgb: (%i, %i, %i)\n",
        type_to_str(w.type),
        w.color.r,
        w.color.g,
	    w.color.b
    );
	// clang-format on
	printf("position: %i %i\n", w.rect.x, w.rect.y);
	printf("size: %i, %i\n", w.rect.dx, w.rect.dy);
	printf("---------------------\n");
}

int main()
{
	printf("layout gui parsing\n");

	const char filename[] = "layout.txt";

	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL) {
		printf("Unable to open file %s.\n", filename);
		return 1;
	}

	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, file) != -1) {
		draw(parse_line(line));
	}

	fclose(file);

	return 0;
}
