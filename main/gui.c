#include <stdio.h>
#include <assert.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xlocale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main/graph.h"

const int WIDTH = 400;
const int HEIGHT = 200;

struct GlobalGUIState {
	Display* display;
	Window root;
	Window win1;
	GC gc;
} GLOBAL_STATE;


void x11_draw_line(int x1, int y1, int x2, int y2)
{
	XDrawLine(
		GLOBAL_STATE.display,
		GLOBAL_STATE.win1,
		GLOBAL_STATE.gc,
		x1, y1, x2, y2
	);
}

int main(int argc, char *argv[])
{
	unsigned long black, white;
	int x, y, pixbyte, i, j;
	XWindowAttributes attr;
	XFontSet font;
	XFontSetExtents *extents;
	char **missing_charset_list_return;
	int missing_charset_count_return;
	char *def_string_return;
	int loop = 1;
	XRectangle inkrect, logrect;
	Atom _NET_WM_NAME;
	Atom _NET_WM_ICON_NAME;
	Atom UTF8_STRING;
	Atom WM_DELETE;
	Atom MESSAGE;
	const char *str = "ハローワールド";
	const char *strs[] = {"ハローワールド", NULL};

	XTextProperty windowname;
	XClassHint classhints;
	XWMHints wmhints;

	setlocale(LC_ALL, "");
	// dpy = XOpenDisplay(NULL);
	GLOBAL_STATE.display = XOpenDisplay(NULL);
	WM_DELETE = XInternAtom(GLOBAL_STATE.display, "WM_DELETE_WINDOW", 0);
	_NET_WM_NAME = XInternAtom(GLOBAL_STATE.display, "_NET_WM_NAME", 0);
	_NET_WM_ICON_NAME = XInternAtom(GLOBAL_STATE.display, "_NET_WM_ICON_NAME", 0);
	UTF8_STRING = XInternAtom(GLOBAL_STATE.display, "UTF8_STRING", 0);
	black = BlackPixel(GLOBAL_STATE.display, 0);
	white = WhitePixel(GLOBAL_STATE.display, 0);
	x = 500;
	y = 500;
	GLOBAL_STATE.root = RootWindow(GLOBAL_STATE.display, 0);
	GLOBAL_STATE.win1 = XCreateSimpleWindow(GLOBAL_STATE.display, GLOBAL_STATE.root, 100, 50, WIDTH, HEIGHT, 0, 0, white);
	XChangeProperty(GLOBAL_STATE.display, GLOBAL_STATE.win1, _NET_WM_NAME, UTF8_STRING, 8, 0, str, strlen(str));
	XChangeProperty(GLOBAL_STATE.display, GLOBAL_STATE.win1, XA_WM_NAME, XA_STRING, 8, 0, str, strlen(str));
	XChangeProperty(GLOBAL_STATE.display, GLOBAL_STATE.win1, _NET_WM_ICON_NAME, UTF8_STRING, 8, 0, str, strlen(str));
	XChangeProperty(GLOBAL_STATE.display, GLOBAL_STATE.win1, XA_WM_ICON_NAME, XA_STRING, 8, 0, str, strlen(str));
	XSelectInput(GLOBAL_STATE.display, GLOBAL_STATE.win1,
			ButtonPressMask | ButtonReleaseMask | ExposureMask | StructureNotifyMask);
	font =
		XCreateFontSet(GLOBAL_STATE.display, "-misc-*-medium-r-normal--14-*-*-*-*-*-*",
				&missing_charset_list_return, &missing_charset_count_return,
				&def_string_return);
	GLOBAL_STATE.gc = XCreateGC(GLOBAL_STATE.display, GLOBAL_STATE.win1, 0, 0);
	XSetBackground(GLOBAL_STATE.display, GLOBAL_STATE.gc, white);
	XSetForeground(GLOBAL_STATE.display, GLOBAL_STATE.gc, black);

	XMapRaised(GLOBAL_STATE.display, GLOBAL_STATE.win1);

	struct Graph g = graph_new(WIDTH, HEIGHT);

	XEvent event;
	while (loop)
	{
		XFlush(GLOBAL_STATE.display);
		if (XEventsQueued(GLOBAL_STATE.display, QueuedAfterFlush) != 0)
		{
			XNextEvent(GLOBAL_STATE.display, &event);
			switch (event.type)
			{
				case ClientMessage:
					MESSAGE = event.xclient.message_type;
					loop = 0;
					break;
				case Expose:
					XGetWindowAttributes(GLOBAL_STATE.display, GLOBAL_STATE.win1, &attr);
					XSetForeground(GLOBAL_STATE.display, GLOBAL_STATE.gc, black);
					Xutf8TextExtents(font, str, strlen(str), &inkrect, &logrect);
					extents = XExtentsOfFontSet(font);
					Xutf8DrawString(GLOBAL_STATE.display, GLOBAL_STATE.win1, font, GLOBAL_STATE.gc,
							(attr.width - logrect.width) / 2,
							(attr.height - logrect.height) / 2 - extents->max_logical_extent.y,
							str, strlen(str));
					XFlush(GLOBAL_STATE.display);

                    // line_draw(graph_line);
					draw_graph(g, x11_draw_line);
					break;
				case ButtonPress:
					printf("ButtonPress\n");
					printf("x = %d,  y = %d\n", event.xbutton.x, event.xbutton.y);
					break;
				case ButtonRelease:
					printf("ButtonRelease\n");
					XGetWindowAttributes(GLOBAL_STATE.display, GLOBAL_STATE.win1, &attr);
					printf("x = %d,  y = %d\n", event.xbutton.x, event.xbutton.y);
					// if (evt.xbutton.x > 0 && evt.xbutton.x < attr.width
					// 		&& evt.xbutton.y > 0 && evt.xbutton.y < attr.height)
					// 	loop = 0;
					break;
			}
		}
	}
    graph_free(&g);
	XFreeFontSet(GLOBAL_STATE.display, font);
	XDestroyWindow(GLOBAL_STATE.display, GLOBAL_STATE.win1);
	XCloseDisplay(GLOBAL_STATE.display);
    return 0;
}
