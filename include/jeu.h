#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/// @file jeu.h
/// @brief Définition des fonctions de jeu

/// @brief Modulo modifié pour traiter correctement les bords i=0 et j=0
/// dans le calcul des voisins avec bords cycliques
/// @param i La ligne ou la colonne à traiter
/// @param m Nombres de lignes ou de colonnes de la grille
static inline int modulo(int i, int m) {return (i+m)%m;}

/// @brief Fait évoluer la grille g d'un pas de temps
/// @param g Pointeur de type grille vers la grille g à faire évoluer
/// @param gc Pointeur de type grille vers gc, copie temporaire de la grille g pour calculer le voisinage
void evolue (grille *g, grille *gc, int* cptEvo);

/// @brief Calcul du voisinage cyclique
/// @param i Ligne i de la grille g
/// @param j Ligne j de la grille g
/// @param g La grille
/// @returns Le nombre de voisins cycliques vivants
int calculCyclique(int i, int j, grille g);

/// @brief Calcul du voisinage non cyclique
/// @param i Ligne i de la grille g
/// @param j Ligne j de la grille g
/// @param g La grille
/// @returns Le nombre de voisins non cycliques vivants
int calculNonCyclique(int i, int j, grille g);

/// @brief Déclaration du pointeur vers le mode de calcul en cours (cyclique ou non cyclique) défini dans io.c
extern int (*compte_voisins_vivants)(int, int, grille);

#endif
