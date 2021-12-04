#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <string.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"

#define SIZEX 900
#define SIZEY 600
#define SIZE_GRILLE 600

/// @file io.h
/// @brief Définition des fonctions de base avant le jeu

#ifdef TEXTE
/// @brief Affichage d'un trait horizontal
/// @param c La longueur du trait
void affiche_trait(int c);

/// @brief Affichage d'une ligne de la grille
/// @param c Longueur de la ligne
/// @param ligne Tableau d'entiers qui représente la ligne
void affiche_ligne(int c, int *ligne);

/// @brief Affichage d'une grille
/// @param g La grille à afficher
void affiche_grille(grille g);

/// @brief Effacement d'une grille
/// @param g La grille à effacer
void efface_grille(grille g);

/// @brief Débute le jeu
/// @param g Pointeur de type grille vers la grille g
/// @param gc Pointeur de type grille vers la grille gc @see evolue
void debut_jeu(grille *g, grille *gc);

#endif

#ifdef GRAPHIQUE

/// @brief Affichage des cellules de la grille avec couleurs selon son état
/// @param surface La surface cairo
/// @param g La grille chargée
void affiche_cellules(cairo_surface_t *surface, grille g);

/// @brief Affichage des lignes de la grille
/// @param surface La surface cairo
/// @param g La grille chargée
void affiche_grille(cairo_surface_t *surface, grille g);

/// @brief Affichage du texte à droite
/// @param surface La surface cairo
void affiche_texte(cairo_surface_t *surface);

/// @brief Reset l'affichage en noir
/// @param surface La surface cairo
void reset_affichage(cairo_surface_t *surface);

/// @brief Reset l'affichage du texte à droite
/// @param surface La surface cairo
void reset_texte(cairo_surface_t *surface);

/// @brief Affichage du menu principal
/// @param surface La surface cairo
void affiche_menu(cairo_surface_t *surface, char* cheminGrille);

/// @brief Débute le jeu
/// @param g Pointeur de type grille vers la grille g
/// @param gc Pointeur de type grille vers la grille gc @see evolue
void debut_jeu(grille *g, grille *gc, char* cheminGrille);

#endif

#endif
