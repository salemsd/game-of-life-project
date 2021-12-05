
#include "io.h"

#if TEXTE

void affiche_trait(int c)
{
	int i;
	for (i = 0; i < c; ++i)
		printf("|---");
	printf("|\n");
	return;
}

int vieillissement = 0; // vieillissement desactivé par défaut
void affiche_ligne(int c, int *ligne)
{
	int i;
	for (i = 0; i < c; ++i)
		if (ligne[i] == 0)
		{
			printf("|   ");
		} // morte representé par un vide
		else if (ligne[i] == -1)
		{
			printf("| X ");
		} // non-viable representé par un X
		else
		{
			if (vieillissement)
			{
				printf("| %d ", ligne[i]);
			} // si vieillissement actif afficher l'âge
			else
			{
				printf("| O ");
			} // sinon afficher O
		}
	printf("|\n");
	return;
}

void efface_grille(grille g)
{
	printf("\n\e[%dA", g.nbl * 2 + 6);
}

int cptEvo = 0; // compteur du temps d'évolution
void affiche_grille(grille g)
{
	int i, l = g.nbl, c = g.nbc;
	printf("\n");
	printf("Temps d'évolution: %d\n", cptEvo);
	affiche_trait(c);
	for (i = 0; i < l; ++i)
	{
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

int (*compte_voisins_vivants)(int, int, grille) = calculNonCyclique; // initialisation du mode de calcul sur non cyclique

void debut_jeu(grille *g, grille *gc)
{
	int valider = 0;
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c)
		{
		case '\n':
		{ // touche "entree" pour évoluer

			if (valider == 0)
			{
				evolue(g, gc, &cptEvo);
				efface_grille(*g);
				affiche_grille(*g);
			}
			else
			{
				valider = 0;
			}

			break;
		}
		case 'n':
		{ // touche "n" pour entrer le nom d'une nouvelle grille

			cptEvo = 0;
			char nomGrille[255];
			printf("Chemin de la grille: \n");
			scanf("%s", nomGrille);
			printf("\n\n");
			libere_grille(g);
			init_grille_from_file(nomGrille, g);
			libere_grille(gc);
			alloue_grille(g->nbl, g->nbc, gc);
			affiche_grille(*g);
			valider = 1;
			//printf("\n[%dA", g->nbl*2);

			break;
		}
		case 'c':
		{
			if (compte_voisins_vivants == calculCyclique) // si cyclique, changer en non cyclique
			{
				compte_voisins_vivants = calculNonCyclique;
				printf("Non cyclique \n");
			}
			else // sinon changer en cyclique
			{
				compte_voisins_vivants = calculCyclique;
				printf("Cyclique \n");
			}

			while (getchar() != '\n')
				;
			printf("\n\e[3A");

			break;
		}

		case 'v':
		{
			if (vieillissement) // si vieillissement actif, désactiver
			{
				vieillissement = 0;
				printf("Vieillissement desactivé \n");
			}
			else // sinon activer
			{
				vieillissement = 1;
				printf("Vieillissement activé \n");
			}

			while (getchar() != '\n')
				;
			printf("\n\e[3A");

			break;
		}

		default:
		{ // touche non traitée
			printf("\n\e[1A");
			break;
		}
		}
		c = getchar();
	}
	return;
}

#endif

#ifdef GRAPHIQUE

int vieillissement = 0;
void affiche_grille(cairo_surface_t *surface, grille g)
{
	// créer un mask et cibler la surface
	cairo_t *cr;
	cr = cairo_create(surface);

	cairo_rectangle(cr, 0, 0, SIZE_GRILLE, SIZE_GRILLE);

	cairo_set_source_rgb(cr, 0.86, 0.86, 0.86); // Blanc
	cairo_set_line_width(cr, 1.5);				// Epaisseur de la grille

	int i, j;
	int l = g.nbl;
	int c = g.nbc;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < c; j++)
		{
			cairo_move_to(cr, ((SIZE_GRILLE * j) / c), 0);
			cairo_line_to(cr, ((SIZE_GRILLE * j) / c), SIZE_GRILLE);
			cairo_move_to(cr, 0, ((SIZE_GRILLE * i) / l));
			cairo_line_to(cr, SIZE_GRILLE, ((SIZE_GRILLE * i) / l));
		}
	}

	cairo_stroke(cr);

	cairo_destroy(cr); // destroy cairo mask
}

void affiche_cellules(cairo_surface_t *surface, grille g)
{
	cairo_t *cr;
	cr = cairo_create(surface);

	int i, j;
	int l = g.nbl;
	int c = g.nbc;

	for (i = 0; i < g.nbl; i++)
	{
		for (j = 0; j < g.nbc; j++)
		{
			// Créer un rectangle pour chaque cellule de la grille
			cairo_rectangle(cr, ((SIZE_GRILLE * j) / c), ((SIZE_GRILLE * i) / l), SIZE_GRILLE / c, SIZE_GRILLE / l);

			// Le remplir avec une couleur selon son état (pour chaque cellule)
			if (!est_nonViable(i, j, g)) // Si la cellule est viable
			{
				if (est_vivante(i, j, g)) // Cellule vivante
				{
					if(vieillissement && g.cellules[i][j] >= 2) // Si le vieillissement est actif et que la cellule a vieilli
					{
						double red = 0.0652 * g.cellules[i][j];
						double green = 0.0678 * g.cellules[i][j];
						double blue = 0.061 * g.cellules[i][j];
						cairo_set_source_rgb(cr, 0.52 - red, 0.78 - green, 0.1 - blue); // La couleur s'assombrit quand l'âge de la cellule augmente
						cairo_fill(cr);
					}
					else // Si vieillissement inactif
					{
						cairo_set_source_rgb(cr, 0.52, 0.78, 0.1); // Jaune
						cairo_fill(cr);					
					}
				}
				else // Cellule morte
				{
					cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); // Gris foncé
					cairo_fill(cr);
				}
			}
			else // Si la cellule est non-viable
			{
				cairo_set_source_rgb(cr, 0.42, 0.1, 0.15); // Rouge foncé
				cairo_fill(cr);
			}
		}
	}

	cairo_destroy(cr);
}

int cptEvo = 0;
int (*compte_voisins_vivants)(int, int, grille) = calculNonCyclique; // initialisation du mode de calcul sur non cyclique

int periode = -2; // Valeur par défaut -2: Oscillation non testée
void affiche_texte(cairo_surface_t *surface)
{
	cairo_t *cr;
	cr = cairo_create(surface);

	// Choisir la police et la taille du texte
	cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 27.0);
	cairo_set_source_rgb(cr, 1, 1, 1); // Blanc

	// Afficher titre
	cairo_move_to(cr, 670, 35);
	cairo_show_text(cr, "Jeu de la vie");

	// Afficher compteur d'évolution
	char *cptEvoChar;
	cptEvoChar = (char *)malloc(4 * sizeof(char));
	// Cast int vers char*
	sprintf(cptEvoChar, "%d", cptEvo);
	cairo_set_font_size(cr, 22.0);
	cairo_move_to(cr, 632, 80);
	cairo_show_text(cr, "Evolution: ");
	cairo_show_text(cr, cptEvoChar);
	free(cptEvoChar);

	// Afficher mode de voisinage
	cairo_move_to(cr, 632, 140);
	if (compte_voisins_vivants == calculNonCyclique)
	{
		cairo_show_text(cr, "Voisinage: Non cyclique");
	}
	else
	{
		cairo_show_text(cr, "Voisinage: Cyclique");
	}

	// Afficher vieillissement
	cairo_move_to(cr, 632, 200);
	if (vieillissement)
	{
		cairo_show_text(cr, "Vieillissement: Actif");
	}
	else
	{
		cairo_show_text(cr, "Vieillissement: Inactif");
	}

	// Afficher oscillation
	cairo_move_to(cr, 632, 260);
	if (periode == -2)
	{
		cairo_show_text(cr, "Oscillation: /");
	}
	else if(periode == -1)
	{
		cairo_show_text(cr, "Oscillation: Non");	
	}
	else
	{	
		cairo_show_text(cr, "Oscillation: ");
		char *periodeChar;
		periodeChar = (char *)malloc(4 * sizeof(char));
		sprintf(periodeChar, "%d", periode);
		cairo_show_text(cr, periodeChar);
		free(periodeChar);
		cairo_show_text(cr, " pas");
	}

	// Afficher controles
	cairo_move_to(cr, 655, 320);
	cairo_set_font_size(cr, 24);
	cairo_show_text(cr, "Contrôles du jeu");

	cairo_move_to(cr, 628, 364);
	cairo_set_font_size(cr, 17);
	cairo_show_text(cr, "(Bouton gauche souris) Évoluer");
	cairo_move_to(cr, 628, 404);
	cairo_show_text(cr, "(c) Switch mode de voisinage");
	cairo_move_to(cr, 628, 444);
	cairo_show_text(cr, "(v) Switch vieillissement");
	cairo_move_to(cr, 628, 484);
	cairo_show_text(cr, "(o) Tester oscillation");
	cairo_move_to(cr, 628, 524);
	cairo_show_text(cr, "(n) Charger une autre grille");
	cairo_move_to(cr, 628, 564);
	cairo_show_text(cr, "(Bouton droit souris) Quitter");

	// Afficher nom
	cairo_move_to(cr, 738, 595);
	cairo_set_font_size(cr, 10);
	cairo_show_text(cr, "Projet TechDev - Salem SAOUDI");

	cairo_destroy(cr);
}

void reset_affichage(cairo_surface_t *surface)
{
	cairo_t *cr;
	cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_paint(cr); // Peint l'arrière plan en noir

	cairo_destroy(cr);
}

void reset_texte(cairo_surface_t *surface)
{
	cairo_t *cr;
	cr = cairo_create(surface);

	cairo_rectangle(cr, SIZE_GRILLE + 1.5, 0, (SIZEX - SIZE_GRILLE), SIZEY); // Rectangle qui recouvre la zone de texte
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_fill(cr); // Remplir le rectangle en noir

	cairo_destroy(cr);
}


void debut_jeu(grille *g, grille *gc, char* cheminGrille)
{
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

	XStoreName(dpy, win, "Jeu de la vie");
	XSelectInput(dpy, win, ExposureMask | ButtonPressMask | KeyPressMask);
	XMapWindow(dpy, win);

	// create cairo surface
	cairo_surface_t *cs;
	cs = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	int commencer = 0;
	while (1)
	{
		XNextEvent(dpy, &e);

		// Premier affichage de la fenetre
		if (e.type == Expose && e.xexpose.count < 1)
		{
			if(commencer)
			{
				affiche_cellules(cs, *g);
				affiche_grille(cs, *g);
				affiche_texte(cs);
			}
			else
			{
				affiche_menu(cs, cheminGrille);
			}	
		}

		// Boutons souris
		// Bouton droit souris - quitter
		else if (e.type == ButtonPress && e.xbutton.button == Button3)
		{
			break;
		}
		// Bouton gauche souris - évolution (ou commencer le jeu)
		else if (e.type == ButtonPress && e.xbutton.button == Button1)
		{
			if(commencer) // Si on est déjà sorti du menu principal, on évolue
			{
				evolue(g, gc, &cptEvo);
				reset_affichage(cs);
				affiche_cellules(cs, *g);
				affiche_grille(cs, *g);
				affiche_texte(cs);
			}
			else // Si on est toujours dans le menu principal, on affiche d'abord la grille sans évoluer
			{
				commencer = 1;
				reset_affichage(cs);
				affiche_cellules(cs, *g);
				affiche_grille(cs, *g);
				affiche_texte(cs);
			}

		}

		// Touches clavier
		// (c) - Switch voisinage cyclique et non cyclique
		else if (e.type == KeyPress && e.xkey.keycode == 54 && commencer) // La condition commencer s'assure qu'on est sorti du menu principal
		{
			if (compte_voisins_vivants == calculCyclique) // si cyclique, changer en non cyclique
			{
				compte_voisins_vivants = calculNonCyclique;
				reset_texte(cs);
				affiche_texte(cs);
			}
			else // sinon changer en cyclique
			{
				compte_voisins_vivants = calculCyclique;
				reset_texte(cs);
				affiche_texte(cs);
			}
		}
		// (v) - Switch activer/désactiver vieillissement
		else if (e.type == KeyPress && e.xkey.keycode == 55 && commencer)
		{
			if (vieillissement) // si vieillissement actif, désactiver
			{
				vieillissement = 0;
				reset_texte(cs);
				affiche_texte(cs);
			}
			else // sinon activer
			{
				vieillissement = 1;
				reset_texte(cs);
				affiche_texte(cs);
			}
		}
		// (n) - Charger une nouvelle grille
		else if (e.type == KeyPress && e.xkey.keycode == 57)
		{
			reset_affichage(cs);
			// Reset l'évolution et le test d'oscillation
			cptEvo = 0;
			periode = -2;
			char nomGrille[255];
			printf("Chemin de la grille: \n");
			scanf("%s", nomGrille);
			printf("\n\n");
			libere_grille(g);
			init_grille_from_file(nomGrille, g);
			libere_grille(gc);
			alloue_grille(g->nbl, g->nbc, gc);
			if(commencer)
			{
				affiche_cellules(cs, *g);
				affiche_grille(cs, *g);
				affiche_texte(cs);
			}
			else
			{
				affiche_menu(cs, nomGrille);
			}
		}
		// (o) - Tester l'oscillation
		else if (e.type == KeyPress && e.xkey.keycode == 32 && commencer)
		{
			periode = grille_oscillante(*g);
			reset_texte(cs);
			affiche_texte(cs);
		}
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy);		   // close the display
}


void affiche_menu(cairo_surface_t *surface, char* cheminGrille)
{
	cairo_t *cr;
	cr = cairo_create(surface);

	// Choisir la police et la taille du texte
	cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 50.0);
	cairo_set_source_rgb(cr, 1, 1, 1); // Blanc

	// Afficher titre
	cairo_move_to(cr, 300, 100);
	cairo_show_text(cr, "Jeu de la vie");

	// Afficher le chemin de la grille chargée
	cairo_move_to(cr, 240, 250);
	cairo_set_font_size(cr, 20.0);
	cairo_show_text(cr, "Vous avez chargé la grille: ");
	cairo_show_text(cr, cheminGrille);

	// Afficher les controles
	cairo_move_to(cr, 290, 390);
	cairo_set_font_size(cr, 17.5);
	cairo_show_text(cr, "(Bouton gauche souris) Commencer");

	cairo_move_to(cr, 320, 430);
	cairo_set_font_size(cr, 17.5);
	cairo_show_text(cr, "(Bouton droit souris) Quitter");

	cairo_move_to(cr, 325, 470);
	cairo_set_font_size(cr, 17.5);
	cairo_show_text(cr, "(n) Charger une autre grille");

	// Afficher nom
	cairo_move_to(cr, 738, 595);
	cairo_set_font_size(cr, 10);
	cairo_show_text(cr, "Projet TechDev - Salem SAOUDI");

	cairo_destroy(cr);
}

#endif
