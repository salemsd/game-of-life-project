#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

int vieillissement = 0; // vieillissement desactivé par défaut
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) { printf ("|   "); } // morte representé par un vide
		else if (ligne[i] == -1) { printf("| X "); } // non-viable representé par un X
		else 
		{
			if(vieillissement) { printf ("| %d ", ligne[i]); } // si vieillissement actif afficher l'âge
			else { 	printf ("| O "); } // sinon afficher O
		}
	printf("|\n");
	return;
}

int cptEvo = 0; // compteur du temps d'évolution
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("Temps d'évolution: %d\n", cptEvo);
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 6); 
}


int (*compte_voisins_vivants)(int, int, grille) = calculNonCyclique; // initialisation du mode de calcul sur non cyclique

void debut_jeu(grille *g, grille *gc){
	int valider = 0;
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				
				if(valider == 0)
				{
					evolue(g, gc);
					cptEvo++;
					efface_grille(*g);
					affiche_grille(*g);
				}
				else{ valider = 0; }

				break;

			}
			case 'n' :
			{ // touche "n" pour entrer le nom d'une nouvelle grille
				
				cptEvo = 0;
				char nomGrille[255];
				printf("Chemin de la grille: \n");
				scanf("%s", nomGrille);
				printf("\n\n");
				libere_grille(g);
				init_grille_from_file(nomGrille, g);
				libere_grille(gc);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g);
				valider = 1;
				//printf("\n[%dA", g->nbl*2);

				break;
			}
			case 'c':
			{
				if(compte_voisins_vivants == calculCyclique) // si cyclique, changer en non cyclique
				{
					compte_voisins_vivants = calculNonCyclique;
					printf("Non cyclique \n");
				}
				else // sinon changer en cyclique
				{
					compte_voisins_vivants = calculCyclique;
					printf("Cyclique \n");
				}

				while(getchar() != '\n');
				printf("\n\e[3A");
				
				break;
			}

			case 'v':
			{
				if(vieillissement) // si vieillissement actif, désactiver
				{
					vieillissement = 0;
					printf("Vieillissement desactivé \n");
				}
				else // sinon activer
				{
					vieillissement = 1;
					printf("Vieillissement activé \n");
				}

				while(getchar() != '\n');
				printf("\n\e[3A");
				
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
