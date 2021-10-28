#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/// @file

/// @brief Affichage d'un trait horizontal
/// @param c La longueur du trait
void affiche_trait (int c);

/// @brief Affichage d'une ligne de la grille
/// @param c Longueur de la ligne
/// @param ligne Tableau d'entiers qui représente la ligne
void affiche_ligne (int c, int* ligne);

/// @brief Affichage d'une grille
/// @param g La grille à afficher
void affiche_grille (grille g);

/// @brief Effacement d'une grille
/// @param g La grille à effacer
void efface_grille (grille g);

/// @brief Débute le jeu
/// @param g Pointeur de type grille vers la grille g
/// @param gc Pointeur de type grille vers la grille gc @see evolue
void debut_jeu(grille *g, grille *gc);

#endif
