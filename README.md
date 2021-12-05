13/10/2021 - TP TechDev Jeu de la vie - Unistra S3 Informatique

Système de versionnement:
- Niveau x: x.0 / Exemple: 2.0 - Niveau 2
- Version y d'un niveau x: x.y / Exemple: 5.1 - Version 1 du niveau 5

Commandes:
- make: Compile le jeu en mode graphique
- make MODE=TEXTE: Compile le jeu en mode texte
- make clean: Efface tout les résidus (obj, doc, bin, dist)
- make dist: Crée une archive .tar.xz avec les include, src, Doxyfile et makefile
- make docs: Genere la documentation html dans un dossier docs

Après compilation:
- Execution: ./bin/main chemin de la grille.txt
