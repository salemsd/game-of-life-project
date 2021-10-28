#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/// @file

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {return (i+m)%m;}

/// @brief Compte le nombre de voisins vivants de la cellule (i,j)
/// les bords sont cycliques.
/// @param i Ligne i de la grille g
/// @param j Ligne j de la grille g
/// @param g La grille
int compte_voisins_vivants (int i, int j, grille g);

/// @brief Fait évoluer la grille g d'un pas de temps
/// @param g Pointeur de type grille vers la grille g à faire évoluer
/// @param gc Pointeur de type grille vers gc, copie temporaire de la grille g pour calculer le voisinage
void evolue (grille *g, grille *gc);

#endif
