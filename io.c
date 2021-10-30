#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
			{ // touche "n" pour entrer le nom d'une nouvelle grille
			    int length = 256;
    			char * nomGrille = malloc(length * sizeof(char));
    			int cpt = 0;
				char c2;
    			printf("Indiquer le chemin du fichier et son nom: ");
				c2 = getchar();
    			while(c2 != '\n')
    			{
        			nomGrille[cpt++] = c2;
        			if (cpt == length)
        			{
    	    			length += 256;
            			nomGrille = realloc(nomGrille, length);
        			}
        			c2 = getchar();
    			}
    			nomGrille[cpt] = '\0';

				libere_grille(g);
				init_grille_from_file(nomGrille, g);
				free(nomGrille);
				libere_grille(gc);
				alloue_grille(g->nbl, g->nbc, gc);

				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
