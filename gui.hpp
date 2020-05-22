#ifndef DEF_GUI
#define DEF_GUI

#include "simulation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#define NB_TEXTURES 5

/** Permet de charger les textures nécessaires à la simulation (grille et ui)
 * @param [out] tabTextures: le tableau de sf::Texture qui contient toutes les textures
 * @param [out] tabSprites: le tableau de sf::Sprites contenant les sprites associées aux textures
 **/
void initTextures(sf::Texture tabTextures[NB_TEXTURES], sf::Sprite tabSprites[NB_TEXTURES]);

/** Détermine la taille en pixel d'une case en fonction de la taille de la grille
 * @return la taille en pixel d'une case dans l'interface graphique
 **/
int initTailleCase();

/** Permet de centrer un texte dans une zone donnée
 * @param [in/out] texte: le texte à centrer
 * @param [in] lmin: la coordonnée en x du coin supérieur droit de la zone
 *					 qui contiendra le texte
 * @param [in] lmax: la coordonnée en x du coin inférieur gauche
 * @param [in] hmin: la coordonnée en y du coin supérieur droit
 * @param [in] hmax: la coordonnée en x du coin inférieur gauche
 * -Les 4 derniers paramètres servent à délimiter une zone qui contiendra le texte
 *  Si l'on veut centrer le texte par rapport à un axe il faut que lmin = lmax (vertical)
 *  et/ou hmin = hmax (horizontal)
 **/
void centrerTexte(sf::Text &texte, uint lmin, uint lmax, uint hmin, uint hmax);

/** Permet de faire tourner un sprite de 90,180 ou 270°
 * @param [in/out] s: le sprite à modifier
 * @param [in] angle: l'angle souhaité pour le sprite
 * @param [in] tailleCase: la taille d'une case dans la grille graphique (utile pour la rotation des elements de la grille)
 **/
void rotation(sf::Sprite &s, int angle, int tailleCase);

/** Permet de représenter la grille dans une fenêtre
 * @param [in] g: la grille contenant les termites et les brindilles
 * @param [in] T: le tableau contenant les termites de la simulation
 * @param [in] tailleCase: la taille en pixel d'une case de la grille
 * @param [out] window: la fenêtre où sera dessinnée la grille
 * @param [in] sprites: le tableau contenant les sprites utilisant les textures de 'textures'
 * @param [in] textures: le tableau contenant les textures utilisées dans la simulation
 **/
void dessineGrille(Grille const& g, tabTermites T, int tailleCase, sf::RenderWindow &window, sf::Sprite sprites[NB_TEXTURES], sf::Texture textures[NB_TEXTURES]);

/** Crée un indicateur de la vitesse (nombre de déplacements en une passe)
 * @param [in] vitesse: le nombre de déplacements en une passe
 * @param [in] police: la police à utiliser pour le texte de l'indicateur
 * @param [in] hauteurFenetre: la hauteur de la fenêtre (en pixel, sert à aligner le texte) 
 * @param [in] largeurFenetre: la largeur de le fenêtre (en pixel, sert à aligner le texte)
 * @return un sf::Text contenant indiquant la "vitesse" de la simulation
 **/
sf::Text compteurVitesse(int vitesse, sf::Font const& police, int const hauteurFenetre, int const largeurFenetre);

/** gère la simulation
 * @param [in] tabTextures: le tableau de sf::Texture qui contient toutes les textures
 * @param [in] tabSprites: le tableau de sf::Sprites contenant les sprites associées aux textures
 * @param [in] tailleCase: la taille d'une case dans la grille graphique
 * @param [in] hauteurFenetre: la hauteur de la fenêtre (en pixel, sert à aligner le texte)
 * @param [in] largeurFenetre: la largeur de le fenêtre (en pixel, sert à aligner le texte)
 * @param [in] fenetre: la fenêtre où seront affichés le différents éléments
 * @return true si on doit recommencer la simulation, false si on doit arrêter
 **/
bool simulation(sf::Texture tabTextures[NB_TEXTURES], sf::Sprite tabSprites[NB_TEXTURES], const int tailleCase, const int hauteurFenetre, const int largeurFenetre, sf::RenderWindow &fenetre);

#endif // DEF_GUI