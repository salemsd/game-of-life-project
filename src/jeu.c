#include "jeu.h"

int calculCyclique(int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int calculNonCyclique(int i, int j, grille g)
{
	int v = 0, l = g.nbl, c = g.nbc;
	
	if(i != 0) // Voisins du haut
	{
		v += est_vivante(i-1, j, g);
		if(j != 0) { v += est_vivante(i-1, j-1, g); }
		if(j != c-1) { v += est_vivante(i-1, j+1, g); }
	}

	if(i != l-1) // Voisins du bas
	{
		v += est_vivante(i+1, j, g);
		if(j != 0) { v += est_vivante(i+1, j-1, g); }
		if(j != c-1) { v += est_vivante(i+1, j+1, g); }
	}

	if(j != 0) { v += est_vivante(i, j-1, g); } // Voisin gauche

	if(j != c-1) { v+= est_vivante(i, j+1, g); } // Voisin droit

	return v;
}

extern int vieillissement; // Déclaration de la variable de vieillissement définie dans io.c
extern int cptEvo; // Déclaration de la variable compteur d'évolution définie dans io.c

void evolue (grille *g, grille *gc, int* cptEvo)
{
	(*cptEvo)++;	
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (!est_nonViable(i, j, *g))
			{	// Si la cellule n'est pas viable, ne fait rien
				v = compte_voisins_vivants(i, j, *gc);
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante
					if (vieillissement == 1) { g->cellules[i][j]++; } // Si vieillissement actif, incrémenter l'âge de la cellule
					if ( v!=2 && v!= 3 ) { set_morte(i,j,*g); }
					if ((g->cellules[i][j] > 8) && vieillissement == 1) { set_morte(i, j, *g); } // Si viellissement actif, et âge > 8, mort de la cellule
				}
				else 
				{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
				}
			}
		}
	}
	
	return;
}
