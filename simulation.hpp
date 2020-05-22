#ifndef DEF_AUTRES
#define DEF_AUTRES

#include "termite.hpp"
#include <vector>

const float DENSITE_TERMITE = 0.20;
const float DENSITE_BRINDILLE = 0.15;

/** indique si un tableau de Coord contient un élément particulier
 * @param [in] c: la coordonnée recherchée
 * @param [in] taille: la taille du tbleau dans lequel on effectue la recherche
 * @param [in] tab: le tableau où l'on cherche la coordonnée c
 * @return true si c est dans tab, false sinon
 **/
bool tabContient(Coord c, int const& taille, Coord tab[]);

/** Gère les déplacements de tous les termites de la simulation
 * @param [in/out] g: la grille contenant les termites et les brindilles
 * @param [in/out] T: le tableau contenant les termites de la simulation
 **/
void deplacement(Grille &g, tabTermites &T);

/** Version de la fonction de déplacmenent permettant de garder la connexité
 *  du tas de brindilles composé des brindilles dont les coordonnées sont dans
 *  coordTas 
 * @param [in/out] g: la grille contenant les termites et les brindilles
 * @param [in/out] T: le tableau contenant les termites de la simulation
 * @param [in] nbBrindilles: le nombre total de brindilles dans la grille
 * @param [in] coordTas: le tableau qui contient les coordonnées des brindilles du plus gros tas
 **/
void deplacement(Grille &g, tabTermites &T, int const& nbBrindilles, Coord coordTas[]);

/** indique si un vecteur contient un élément particulier
 * @param [in] c: la coordonnée recherchée
 * @param [in] tab: le vecteur où l'on cherche la coordonnée c
 * @return true si c est dans tab, false sinon
 **/
bool contient(Coord c, std::vector<Coord> const& tab);

/** Permet de récuperer les coordonnées des brindilles d'un tas
 * @param [in] g: la grille contenant les termites et les brindilles
 * @param [in] depart: la coordonée par laquelle on commence le parcours du tas
 * @param [out] explores: le vecteur contenant les coordonnées des brindilles
 *				explorées lors du parcours
 **/
void tas(Grille const& g, Coord depart, std::vector<Coord> &explores);

/** indique la taille du plus gros tas de brindilles
 * @param [in] g: la grille contenant les termites et les brindilles
 * @param [in] maxBrindilles: le nombre total de brindilles dans la grille
 * @param [out] coordTas: le tableau qui contient les coordonnées des brindilles du plus gros tas
 * @return le nombre de brindilles qui composent le plus gros tas
 **/
int tailleMaxTas(Grille const& g, int const& maxBrindilles, Coord coordTas[]);

/** initialise la grille de la simulation
 * @param [out] g: la grille contenant les termites et les brindilles
 * @param [in/out] T: le tableau contenant les termites de la simulation
 * @return le nombre total de brindilles de la grille
 **/
int initGrille(Grille &g, tabTermites &T);

/** initialise le tableau qui contiendra les coordonnées des brindilles
 ** appartenant au plus gros tas
 * @param [in] taille: la taille du tableau (qui est égale au nombre total de brindilles)
 * @param [out] tabTas: le tableau initialisé à vide
 **/
void initTabTasVide(int const taille, Coord tabTas[]);

#endif // DEF_AUTRES