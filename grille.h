#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/// @file grille.h
/// @brief Définitions de toutes les fonctions en rapport avec la grille

/// @brief Structure grille
/// @param nbl Nombre de lignes
/// @param nbc Nombre de colonnes
/// @param cellules Tableau de tableau de cellules
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/// @brief Alloue une grille de taille l*c, et initialise toutes les cellules à mortes
/// @param l Nombre de lignes
/// @param c Nombre de colonnes
/// @param g Pointeur de type grille vers la grille à allouer @see grille
void alloue_grille (int l, int c, grille* g);

/// @brief Libère une grille
/// @param g Pointeur de type grille vers la grille à liberer @see grille
void libere_grille (grille* g);

/// @brief Alloue et initialise la grille g à partir d'un fichier
/// @param filename Le nom du fichier contenant la grille
/// @param g Pointeur de type grille vers la grille à allouer et initialiser @see grille
void init_grille_from_file (char * filename, grille* g);

/// @brief Rend vivante la cellule (i,j) de la grille g
/// @param i Ligne i de la grille
/// @param j Colonne j de la grille
/// @param g La grille @see grille
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/// @brief Rend morte la cellule (i,j) de la grille g
/// @param i Ligne i de la grille
/// @param j Colonne j de la grille
/// @param g La grille @see grille
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/// @brief Teste si la cellule (i,j) de la grille g est vivante
/// @param i Ligne i de la grille
/// @param j Colonne j de la grille
/// @param g La grille @see grille
/// @returns 0 si la cellule est morte, 1 si la cellule est vivante
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] == 1;}

/// @brief Recopie la grille gs dans gd (sans allocation)
/// @param gs La grille du début gs
/// @param gd La grille de destination gd
void copie_grille (grille gs, grille gd);

#endif
