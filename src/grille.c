#include "grille.h"
#include "jeu.h"

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	int nonViables = 0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", & nonViables); // récupere le nombre de cellules non-viables
	for (n=0; n< nonViables; ++n){
		fscanf(pfile, "%d", & i); // récuperer ligne i de la cellule non-viable
		fscanf(pfile, "%d", & j); // récuperer colonne j de la cellule non-viable
		set_nonViable(i,j,*g); // cellule = -1
	}
	
	fclose (pfile);
	return;
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

void alloue_grille (int l, int c, grille* g)
{
	int i, j;
	g->nbl = l;
	g->nbc = c;
	g->cellules = malloc(g->nbl * sizeof(int*));

	for (i = 0; i < g->nbl; i++)
    {
		g->cellules[i] = malloc(g->nbc * sizeof(int));
    }

    for (i = 0; i < g->nbl; i++)
    {
        for (j = 0; j < g->nbc; j++)
        {
            set_morte(i, j, *g);
        }
    }

}

void libere_grille (grille* g)
{
    int i;

    for (i = 0; i < g->nbl; i++)
    {
		free(g->cellules[i]);
    }
    free(g->cellules);
}


int cellules_identiques(grille g, grille gc)
{
	if(g.nbc != gc.nbc && g.nbl != gc.nbl) { return 0; } // Si la taille des grilles n'est pas identique
	
	int i, j;
	int l = g.nbl, c = g.nbc;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < c; j++)
		{
			if(g.cellules[i][j] != gc.cellules[i][j]) { return 0; } // Si une seule cellule n'est pas identique retourne 0
		}
	}
	
	return 1; // Si la condition du haut n'est pas vraie, la fonction retournera toujours 1
}


int vide(grille g)
{
	int i, j;
	int l = g.nbl, c = g.nbc;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < c; j++)
		{
			if (est_vivante(i, j, g)) // Si il y a une cellule vivante alors la grille n'est pas vide
			{
				return 0;
			}
		}
	}
	return 1;
}

int grille_oscillante(grille g)
{
	int i;
	int l = g.nbl, c = g.nbc;

	// tempEvo: copie qui évoluera à chaque pas
	// tempEvo2: copie qui évoluera chaque 1000 pas
	// temp: pour la fonction evolue
	grille temp, tempEvo, tempEvo2;

	alloue_grille(l, c, &temp);
	alloue_grille(l, c, &tempEvo);
	alloue_grille(l, c, &tempEvo2);
	copie_grille(g, tempEvo);
	copie_grille(g, tempEvo2);

	int max = 1000; // L'oscillation ne sera plus testée au dela de 1000 pas ET la grille n'évoluera plus au dela de 1000 évolutions

	int periode = 0;
	int identique = 0;
	for (i = 0; i < max; i++)
	{
		while(periode < max && !identique) // Si les deux grilles sont identiques, sors de la boucle
		{
			evolue(&tempEvo, &temp, &periode); // On évolue la grille temporaire
		
			if (vide(tempEvo)) { return -1; } // Pour éviter de tester deux grilles vides identiques. Si elle est vide c'est qu'elle n'oscille pas 
		
			identique = cellules_identiques(tempEvo2, tempEvo);
		}

		if(!identique) // Si on n'a pas trouvé d'oscillation pour la grille initiale, on l'évolue et on recommence
		{
			evolue(&tempEvo2, &temp, &periode); // évolue la grille initiale d'un pas
			periode = 0; // reset la période
			copie_grille(tempEvo2, tempEvo); // copie la grille initiale évoluée dans tempEvo
		}
		else { break; }
	}

	libere_grille(&temp);
	libere_grille(&tempEvo);
	libere_grille(&tempEvo2);

	if(identique) { return periode; }
	else { return -1; }
}

