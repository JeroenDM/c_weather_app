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

Display *dpy;
Window root, win;
XEvent evt;
GC gc;

void x11_draw_line(int x1, int y1, int x2, int y2)
{
	XDrawLine(dpy, win, gc, x1, y1, x2, y2);
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
	dpy = XOpenDisplay(NULL);
	WM_DELETE = XInternAtom(dpy, "WM_DELETE_WINDOW", 0);
	_NET_WM_NAME = XInternAtom(dpy, "_NET_WM_NAME", 0);
	_NET_WM_ICON_NAME = XInternAtom(dpy, "_NET_WM_ICON_NAME", 0);
	UTF8_STRING = XInternAtom(dpy, "UTF8_STRING", 0);
	black = BlackPixel(dpy, 0);
	white = WhitePixel(dpy, 0);
	x = 500;
	y = 500;
	root = RootWindow(dpy, 0);
	win = XCreateSimpleWindow(dpy, root, 100, 50, WIDTH, HEIGHT, 0, 0, white);
	XChangeProperty(dpy, win, _NET_WM_NAME, UTF8_STRING, 8, 0, str, strlen(str));
	XChangeProperty(dpy, win, XA_WM_NAME, XA_STRING, 8, 0, str, strlen(str));
	XChangeProperty(dpy, win, _NET_WM_ICON_NAME, UTF8_STRING, 8, 0, str, strlen(str));
	XChangeProperty(dpy, win, XA_WM_ICON_NAME, XA_STRING, 8, 0, str, strlen(str));
	XSelectInput(dpy, win,
			ButtonPressMask | ButtonReleaseMask | ExposureMask | StructureNotifyMask);
	font =
		XCreateFontSet(dpy, "-misc-*-medium-r-normal--14-*-*-*-*-*-*",
				&missing_charset_list_return, &missing_charset_count_return,
				&def_string_return);
	gc = XCreateGC(dpy, win, 0, 0);
	XSetBackground(dpy, gc, white);
	XSetForeground(dpy, gc, black);

	XMapRaised(dpy, win);

	struct Graph g = graph_new(WIDTH, HEIGHT);

	while (loop)
	{
		XFlush(dpy);
		if (XEventsQueued(dpy, QueuedAfterFlush) != 0)
		{
			XNextEvent(dpy, &evt);
			switch (evt.type)
			{
				case ClientMessage:
					MESSAGE = evt.xclient.message_type;
					loop = 0;
					break;
				case Expose:
					XGetWindowAttributes(dpy, win, &attr);
					XSetForeground(dpy, gc, black);
					Xutf8TextExtents(font, str, strlen(str), &inkrect, &logrect);
					extents = XExtentsOfFontSet(font);
					Xutf8DrawString(dpy, win, font, gc,
							(attr.width - logrect.width) / 2,
							(attr.height - logrect.height) / 2 - extents->max_logical_extent.y,
							str, strlen(str));
					XFlush(dpy);

                    // line_draw(graph_line);
					draw_graph(g, x11_draw_line);
					break;
				case ButtonPress:
					printf("ButtonPress\n");
					printf("x = %d,  y = %d\n", evt.xbutton.x, evt.xbutton.y);
					break;
				case ButtonRelease:
					printf("ButtonRelease\n");
					XGetWindowAttributes(dpy, win, &attr);
					printf("x = %d,  y = %d\n", evt.xbutton.x, evt.xbutton.y);
					// if (evt.xbutton.x > 0 && evt.xbutton.x < attr.width
					// 		&& evt.xbutton.y > 0 && evt.xbutton.y < attr.height)
					// 	loop = 0;
					break;
			}
		}
	}
    graph_free(&g);
	XFreeFontSet(dpy, font);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
    return 0;
}
