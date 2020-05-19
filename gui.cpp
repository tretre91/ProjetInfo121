#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include "autres.hpp"
using namespace std;

const int NB_TEXTURES = 5;

/** Permet de charger les textures nécessaires à la simulation (grille et ui)
 * @param [out] tabTextures: le tableau de sf::Texture qui contient toutes les textures
 * @param [in] path: le chemin vers le dossier où a eu lieu la compilation
 **/
void initTextures(sf::Texture tabTextures[NB_TEXTURES], sf::Sprite tabSprites[NB_TEXTURES]){
	if(!tabTextures[0].loadFromFile("Ressources/termite_n.png")) // texture de termite droit
		cout << "Echec du chargement de la texture termite_droit" << endl;
	
	if(!tabTextures[1].loadFromFile("Ressources/termite_no.png")) // texture de termite penché (en diagonale)
		cout << "Echec du chargement de la texture termite_penche" << endl;
	
	if(!tabTextures[2].loadFromFile("Ressources/brindille.png")) // texture de brindille
		cout << "Echec du chargement de la texture brindille" << endl;
	
	if(!tabTextures[3].loadFromFile("Ressources/termite_charge_n.png")) // texture de termite droit qui porte une brindille
		cout << "Echec du chargement de la texture termite_charge_droit" << endl;
	
	if(!tabTextures[4].loadFromFile("Ressources/termite_charge_no.png")) // texture de termite penché qui porte une brindille
		cout << "Echec du chargement de la texture termite_charge_penche" << endl;
	
	for(int i = 0; i < NB_TEXTURES; i++)
		tabSprites[i].setTexture(tabTextures[i]);
}

/** Détermine la taille en pixel d'une case en fonction de la taille de la grille
 * @return la taille en pixel d'une case dans l'interface graphique
 **/
int initTaileCase(){
	int tailleCase = 30;
	if(TAILLE > 75)
		tailleCase = 6;
	else if(TAILLE > 50)
		tailleCase = 10;
	else if(TAILLE > 39)
		tailleCase = 15;
	else if(TAILLE > 30)
		tailleCase = 20;
	else if(TAILLE > 25)
		tailleCase = 25;
	return tailleCase;
}

void centrerTexte(sf::Text &texte, uint lmin, uint lmax, uint hmin, uint hmax){
	texte.setPosition(lmin + (lmax - lmin - texte.getGlobalBounds().width)/2, hmin + (hmax - hmin - texte.getGlobalBounds().height)/2);
}

/** Permet de faire tourner un sprite de 90,180 ou 270°
 * @param [in/out] s: le sprite à modifier
 * @param [in] angle: l'angle souhaité pour le sprite
 * @param [in] tailleCase: la taille d'une case dans la grille graphique (utile pour la rotation des elements de la grille)
 **/
void rotation(sf::Sprite &s, int angle, int tailleCase){
	sf::Vector2f scale = s.getScale();
	sf::Vector2f pos = s.getPosition();
	s.rotate(angle);
	switch(angle){
		case 90: s.setPosition(pos.x + scale.x*tailleCase, pos.y); break;
		case 180: s.setPosition(pos.x + scale.x*tailleCase, pos.y + scale.y*tailleCase); break;
		case 270: s.setPosition(pos.x, pos.y + scale.y*tailleCase); break;
		default: break;
	}
}

void dessineGrille(Grille const& g, tabTermites T, int tailleCase, sf::RenderWindow &window, sf::Sprite sprites[NB_TEXTURES], sf::Texture textures[NB_TEXTURES]){
	sf::Sprite temp;
	int texture1 = 0;
	int texture2 = 1;
	bool dessin = false;
	
	for(int i = 0; i < TAILLE; i++)
		for(int j = 0; j < TAILLE; j++){
			if(contientBrindille(g, {i,j})){
				dessin = true;
				temp = sprites[2];
				temp.setPosition(tailleCase*j, tailleCase*i);
			} else if(numeroTermite(g, {i,j}) >= 0){
				dessin = true;
				if(porteBrindille(T.tab[numeroTermite(g, {i,j})])){
					texture1 = 3;
					texture2 = 4;
				}
				switch(directionTermite(T.tab[numeroTermite(g, {i,j})])){
					case NO:temp = sprites[texture2];
							temp.setPosition(tailleCase*j, tailleCase*i);
							break;
					case  N:temp = sprites[texture1];
							temp.setPosition(tailleCase*j, tailleCase*i);
							break;
					case NE:temp = sprites[texture2];
							temp.setPosition(tailleCase*j, tailleCase*i);
							rotation(temp, 90, tailleCase);
							break;
					case  E:temp = sprites[texture1];
							temp.setPosition(tailleCase*j, tailleCase*i);
							rotation(temp, 90, tailleCase);
							break;
					case SE:temp = sprites[texture2];
							temp.setPosition(tailleCase*j, tailleCase*i);
							rotation(temp, 180, tailleCase);
							break;
					case  S:temp = sprites[texture1];
							temp.setPosition(tailleCase*j, tailleCase*i);
							rotation(temp, 180, tailleCase);
							break;
					case SO:temp = sprites[texture2];
							temp.setPosition(tailleCase*j, tailleCase*i);
							rotation(temp, 270, tailleCase);
							break;
					case  O:temp = sprites[texture1];
							temp.setPosition(tailleCase*j, tailleCase*i);
							rotation(temp, 270, tailleCase);
							break;
				}
			}
			if(dessin){
				temp.setScale(tailleCase/30., tailleCase/30.);
				window.draw(temp);
				dessin = false;
			}
			texture1 = 0;
			texture2 = 1;
		}
}

int main(){
	/* Chargement des textures */
	sf::Texture tabTextures[NB_TEXTURES];
	sf::Sprite tabSprites[NB_TEXTURES];
	initTextures(tabTextures, tabSprites);
	
	/* determination de la taille d'une case (en pixel) */
	int tailleCase = initTaileCase();
	
	/* initialisation des grilles et tableaux de la simulation */
	srand(time(0));
    tabTermites tabT;
    tabVide(tabT);
    Grille g;
	const int maxBrindilles = initGrille(g, tabT);
    Coord grosTas[maxBrindilles];
	for(int i = 0; i < maxBrindilles; i++)
		grosTas[i] = {-1, -1};
	
	/* initialisation des variables nécessiars à l'interaction utilisateur */
	int nbPasse = 1;
	bool passeAuto = false;
	int tailleTas = 0;
	int maxTailleTas = 0;
	bool verifTailleTas = false;
	bool logTailleTas = true;
	
	/* Génération des autres objets (bordures, déco, boutons ...) */
	const int hauteurFenetre = tailleCase*TAILLE;
	const int largeurFenetre = hauteurFenetre + 250;
	
	sf::RectangleShape separateur(sf::Vector2f(5, hauteurFenetre));
	separateur.setFillColor(sf::Color::Black);
	separateur.setPosition(hauteurFenetre, 0);
	
	sf::Font arial;
	if(!arial.loadFromFile("Ressources/arial.ttf"))
		cout << "Impossible de charger la police arial.ttf";
	
	string const vitesse = "Vitesse : x";
	sf::Text texteVitesse("", arial, 25);
	texteVitesse.setString(vitesse + to_string(nbPasse));
	centrerTexte(texteVitesse, hauteurFenetre, largeurFenetre, 0, hauteurFenetre);
	
	sf::Text texteMode("Mode : Manuel", arial, 25);
	centrerTexte(texteMode, hauteurFenetre, largeurFenetre, 5, 5);
	
	string const t_tailleTas = "Taille du plus \n gros tas : ";
	sf::Text texteTailleTas("Taille du plus \n gros tas : 0", arial, 25);
	centrerTexte(texteTailleTas, hauteurFenetre, largeurFenetre, hauteurFenetre - 70, hauteurFenetre - 70);
	
	sf::Text texteMaxTailleTas("Max : 0 brindilles", arial, 25);
	centrerTexte(texteMaxTailleTas, hauteurFenetre, largeurFenetre, hauteurFenetre - 25, hauteurFenetre - 25);
	
	/* création de la fenêtre */
	sf::RenderWindow fenetre(sf::VideoMode(largeurFenetre, hauteurFenetre), "simulation termites", 5);
	fenetre.setVerticalSyncEnabled(false);
	fenetre.setFramerateLimit(60);
	
	
	while(fenetre.isOpen()){
		sf::Event event;
		while(fenetre.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
					fenetre.close();
					break;
				case sf::Event::KeyPressed:
					switch(event.key.code){
						case sf::Keyboard::Q:
							fenetre.close();
							break;
						case sf::Keyboard::Return:
							if(!passeAuto)
								for(int i = 0; i < nbPasse; i++){
									deplacement(g, tabT, maxBrindilles, grosTas);
									if(logTailleTas){
										tailleTas = tailleMaxTas(g, maxBrindilles, grosTas);
										if(tailleTas > maxTailleTas)
											maxTailleTas = tailleTas;
									}
								}
							break;
						case sf::Keyboard::Multiply:
						case sf::Keyboard::Up:
							nbPasse *= 2;
							texteVitesse.setString(vitesse + to_string(nbPasse));
							centrerTexte(texteVitesse, hauteurFenetre, largeurFenetre, 0, hauteurFenetre);
							break;
						case sf::Keyboard::Slash:
						case sf::Keyboard::Down:
							if(nbPasse > 1){
								nbPasse /= 2;
								texteVitesse.setString(vitesse + to_string(nbPasse));
								centrerTexte(texteVitesse, hauteurFenetre, largeurFenetre, 0, hauteurFenetre);
							}
							break;
						case sf::Keyboard::A:
							passeAuto = !passeAuto;
							if(passeAuto)
								texteMode.setString("Mode : Automatique");
							else
								texteMode.setString("Mode : Manuel");
							centrerTexte(texteMode, hauteurFenetre, largeurFenetre, 5, 5);
							break;
						case sf::Keyboard::M:
							verifTailleTas = !verifTailleTas;
							break;
						case sf::Keyboard::L:
							logTailleTas = !logTailleTas;
							break;
						case sf::Keyboard::C:
							tabVide(tabT);
							initGrille(g, tabT);
							nbPasse = 1;
							passeAuto = false;
							tailleTas = 0;
							maxTailleTas = 0;
							texteVitesse.setString(vitesse + to_string(nbPasse));
							centrerTexte(texteVitesse, hauteurFenetre, largeurFenetre, 0, hauteurFenetre);
							break;
						default: break;
					}
				default: break;
			}
		}
		fenetre.clear(sf::Color(217, 160, 48));
		
		if(passeAuto)
			for(int i = 0; i < nbPasse; i++){
				deplacement(g, tabT, maxBrindilles, grosTas);
				if(logTailleTas){
					tailleTas = tailleMaxTas(g, maxBrindilles, grosTas);
					if(tailleTas > maxTailleTas)
						maxTailleTas = tailleTas;
				}
			}
		
		dessineGrille(g, tabT, tailleCase, fenetre, tabSprites, tabTextures);
		fenetre.draw(separateur);
		fenetre.draw(texteVitesse);
		fenetre.draw(texteMode);
		if(logTailleTas){
			texteMaxTailleTas.setString("Max : " + to_string(maxTailleTas) + " brindilles");
			fenetre.draw(texteMaxTailleTas);
			if(verifTailleTas){
				texteTailleTas.setString(t_tailleTas + to_string(tailleTas));
				fenetre.draw(texteTailleTas);
			}
		}
		
		fenetre.display();
	}
	return 0;
}