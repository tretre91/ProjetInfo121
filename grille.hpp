#ifndef DEF_GRILLE
#define DEF_GRILLE

#include "coord.hpp"

const int TAILLE = 20;

struct Case{
    int contenu; // -2 pour une brindille, -1 pour une case vide, un nombre >0 pour un termite
};

struct Grille{
    Case t[TAILLE][TAILLE];
};



/** Modifie une case pour la rendre vide
 **/
void initialiseCaseVide(Case &c);

/** Permet de créer une grille vide
 * @param [in/out] g la grille devant être vidée
 **/
void initialiseGrilleVide(Grille &g);

/** Vérifie si une case d'une grille est vide
 * @param [in] c la position de la case dans la grille
 * @param [in] g la grille contenant la case
 * @return true si la case aux coordonnées spécifiées est vide
 **/
bool estVide(Grille g, Coord c);

/** Vérifie la position indiquée est dans une grille
 * @param [in] c la position à vérifier
 * @return true si la position indiquée est bien dans la grille
 **/
bool dansGrille(Grille g, Coord c);

/** Vérifie si la case indiquée contient une brindille
 * @param [in] g la grille contenant la case
 * @param [in] c la position de la case dans la grille
 * @return true si la case aux coordonnées spécifiées contient une brindille
 **/
bool contientBrindille(Grille g, Coord c);

/** Indique le numéro du termite présent sur la case spécifiée
 * @param [in] g la grille contenant la case
 * @param [in] c la position de la case dans la grille
 * @return le numéro du termite qui est sur la case ou -1 si il n'y a pas de termite sur cette case
 **/
int numeroTermite(Grille g, Coord c);

/** Modifie une case de la grille pour y contenir une brindille
 * @param [in/out] g la grille à modifier
 * @param [in] c la position dans la grille de la case à modifier
 **/
void poseBrindille(Grille &g, Coord c);

/** Modifie une case de la grille pour y enlever une brindille
 * @param [in/out] g la grille à modifier
 * @param [in] c la position dans la grille de la case à modifier
 **/
void enleveBrindille(Grille &g, Coord c);

/** Modifie une case de la grille pour y contenir un termite
 * @param [in/out] g la grille à modifier
 * @param [in] c la position dans la grille de la case à modifier
 * @param [in] numTermite le numero associé au termite à poser dans la case
 **/
void poseTermite(Grille &g, Coord c, int numTermite);

/** Modifie une case de la grille pour y enlever un termite
 * @param [in/out] g la grille à modifier
 * @param [in] c la position dans la grille de la case à modifier
 **/
void enleveTermite(Grille &g, Coord c);

#endif