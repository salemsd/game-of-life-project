College project - Conway's Game of Life using C

Projet TechDev Jeu de la vie L2 Informatique

Système de versionnement:
- Niveau x: x.0 / Exemple: 2.0 - Niveau 2
- Version y d'un niveau x: x.y / Exemple: 5.1 - Version 1 du niveau 5

Commandes:
- make: Compile le jeu en mode graphique
- make MODE=TEXTE: Compile le jeu en mode texte
- make clean: Efface tout les résidus (obj, doc, bin, dist)
- make dist: Crée une archive .tar.xz avec les include, src, Doxyfile et makefile
- make docs: Genere la documentation html dans un dossier docs

Commands:
- make: Compiles the game in GUI mode
- make MODE=TEXTE: Compiles the game in terminal mode
- make clean: Cleans all unnecessary files (obj, doc, bin, dist)
- make dist: Creates a .tar.xz archive with the code, the Doxyfile, and the makefile
- make docs: Generates html documentation in a doc folder

Execution:
- ./bin/main grilles/grille{num}.txt
