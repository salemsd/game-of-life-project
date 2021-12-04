#include <stdio.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"


int main(int argc, char **argv)
{

	if (argc != 2)
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1], &g);
	alloue_grille(g.nbl, g.nbc, &gc);

#ifdef TEXTE

	affiche_grille(g);

	debut_jeu(&g, &gc);

#endif

//#ifdef GRAPHIQUE

	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

	// init the display
	if (!(dpy = XOpenDisplay(NULL)))
	{
		fprintf(stderr, "Erreur: impossible d'afficher la fenetre\n");
		exit(1);
	}

	scr = DefaultScreen(dpy);
	rootwin = RootWindow(dpy, scr);

	win = XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
							  BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Jeu de la vie - SAOUDI Salem");
	XSelectInput(dpy, win, ExposureMask | ButtonPressMask | KeyPressMask);
	XMapWindow(dpy, win);

	// create cairo surface
	cairo_surface_t *cs;
	cs = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	while (1)
	{
		XNextEvent(dpy, &e);
		if (e.type == Expose && e.xexpose.count < 1)
		{
	
			affiche_cellules(cs, g);
			affiche_grille(cs, g);

		}
		else if (e.type == ButtonPress)
			break;
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy);		   // close the display

//#endif

	libere_grille(&g);
	libere_grille(&gc);

	return 0;
}
