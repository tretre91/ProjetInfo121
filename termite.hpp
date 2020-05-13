#include "grille.hpp"
#include <cstdlib>

struct Termite{
    int numero;
    Coord position;
    Direction direction;
    bool charge;
	bool tournerSurPlace;
	int sablier;
};

struct tabTermites{
    Termite tab[(TAILLE*TAILLE)/10];
    int taille;
};

/** Déclare un tableau de termites comme étant vide
 * @param [out] T le tableau de termites à vider
 **/
void tabVide(tabTermites &T);

/** Indique le nombre d'éléments d'un tableau de termites
 * @param [in] T le tableau de termites
 * @return le nombre de termites de T
 **/
int tailleTableau(tabTermites T);

/** Indique si un tableau de termites est plein
 * @param [in] T le tableau des termites de la simulation
 * @return true si le tableau est plein, false sinon
 **/
bool estPlein(tabTermites T);

/** Crée un nouveau termite dans le tableau de termites (si il n'est pas plein)
 * @param [in/out] T le tableau des termites de la simulation
 **/
void creeTermite(tabTermites &T, Coord c);



/** Indique la direction du termite
 * @param [in] t le termite dont on souhaite connaitre l'orientation
 * @return la direction du termite en question
 **/
Direction directionTermite(Termite t);

/** Indique les coordonnées de la case en face du termite
 * @param [in] t un termite
 * @return les coordonnées de la case située en face de t
 **/
Coord devantTermite(Termite t);

/** Vérifie si un termite porte une brindille
 * @param [in] t un termite
 * @return true si t porte une brindille
 **/
bool porteBrindille(Termite t);

/** Permet de faire tourner un termite à droite
 * @param [in/out] t un termite
 **/
void tourneADroite(Termite &t);

/** Permet de faire tourner un termite à gauche
 * @param [in/out] t un termite
 **/
void tourneAGauche(Termite &t);

/** Permet de faire tourner un termite dans une direction aléatoire
 * @param [in/out] t un termite
 **/
void tourneAleat(Termite &t);



/** Vérifie si la case en face d'un termite est vide
 * @param [in] g la grille de jeu
 * @param [in] t un termite
 * @return true si la case en face du termite est vide
 **/
bool laVoieEstLibre(Grille g, Termite t);

/** Vérifie si la case en face d'un termite contient une brindille
 * @param [in] g la grille de jeu
 * @param [in] t un termite
 * @return true si la case en face du termite contient une brindille
 **/
bool brindilleEnFace(Grille g, Termite t);

bool murEnFace(Grille g, Termite t);

/** Vérifie si un termite ne s'enferme pas s'il pose une brindille en face de lui
 * @param [in] g la grille de jeu
 * @param [in] t un termite
 * @return true si le termite ne peut pas s'enfermer (càd si il y a au moins 2 cases libres
 *     autour de lui avant le depôt de sa brindille
 **/
bool pasEnferme(Grille g, Termite t);



/** Permet de faire avancer un termite sur la case en face de lui
 * @param [in/out] g la grille de jeu
 * @param [in/out] t le termite à faire avancer
 **/
void avanceTermite(Grille &g, Termite &t);

/** Permet a un termite qui porte une brindille de la déposer (la case devant lui est supposée vide)
 * @param [in/out] g la grille de jeu
 * @param [in/out] t le termite que l'on souhaite débarrasser de sa brindille
 **/
void dechargeTermite(Grille &g, Termite &t);

/** Permet a un termite de rammasser une brindille (la case devant lui est supposée en contenir une)
 * @param [in/out] g la grille de jeu
 * @param [in/out] t le termite que l'on souhaite charger
 **/
void chargeTermite(Grille &g, Termite &t);

/** Permet de déplacer aléatoirement le termite
 * @param [in/out] g la grille de jeu
 * @param [in/out] t le termite que l'on souhaite déplacer
 **/
void marcheAleatoire(Grille &g, Termite &t);

void modifierSablier(Termite &t);

int sablier(Termite t);