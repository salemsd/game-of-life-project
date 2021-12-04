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
		printf("usage : ./bin/main <chemin du fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1], &g);
	alloue_grille(g.nbl, g.nbc, &gc);

#ifdef TEXTE

	affiche_grille(g);

	debut_jeu(&g, &gc);

#endif

#ifdef GRAPHIQUE

	debut_jeu(&g, &gc, argv[1]);

#endif

	libere_grille(&g);
	libere_grille(&gc);

	return 0;
}
