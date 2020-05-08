# ProjetInfo121

1 **Changements précédents**
* Affichage de la grille et de la direction des termite
* ~~Ajout d'une interface graphique, d'une classe 'Bouton' servant à créer des boutons~~
* ~~Correction du bug sur le resize des 'BoutonTexte'~~
* ~~Ajout d'options d'édition du style de la légende des 'BoutonTexte'~~
* Ajout d'une documentation en html et en LaTeX générée avec doxygen
* Changement du titre du projet dans la doc ~~et ajout d'une formule dans le makefile pour générer la documentation~~

2 Nouveau : **Suppression de la classe Bouton et de ses classes filles**

3 Nouveau : **Refonte du code de l'interface graphique**
* Suppression du tableau de sprite
* Utilisation d'un seul sprite que l'on change selon l'objet à dessiner et dont l'on modifie la position
* Ajout d'interactions claviers (modification de la "vitesse" et fermeture de la fenetre)

4 **Avancement dans le projet**
* Ajout du ramassage et du depot de brindilles
* Ajout d'une fonction qui gère les déplacements des termites à chaque tour
* Simulation fonctionnelle, restes toutefois des choses à modifier dans le comportement des termites