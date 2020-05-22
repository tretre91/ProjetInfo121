#include "gui.hpp"
#include <string>
#include <cstdlib>
using namespace std;

int main(){
	/* Chargement des textures */
	sf::Texture tabTextures[NB_TEXTURES];
	sf::Sprite tabSprites[NB_TEXTURES];
	initTextures(tabTextures, tabSprites);
	
	/* determination de la taille d'une case (en pixel) */
	int tailleCase = initTailleCase();
	
	/* initialisation des grilles et tableaux de la simulation */
	srand(time(0));
	tabTermites tabT;
	tabVide(tabT);
	Grille g;
	const int maxBrindilles = initGrille(g, tabT);
	Coord grosTas[maxBrindilles];
	initTabTasVide(maxBrindilles, grosTas);
	
	/* initialisation des variables nécessiars à l'interaction utilisateur */
	int nbPasse = 1;
	bool passeAuto = false;
	int tailleTas = 0;
	bool logTailleTas = true;
	bool connexe = false;
	
	/* Génération des autres objets (bordures, légendes...) */
	const int hauteurFenetre = tailleCase*TAILLE;
	const int largeurFenetre = hauteurFenetre + 250;
	
	sf::RectangleShape separateur(sf::Vector2f(5, hauteurFenetre));
	separateur.setFillColor(sf::Color::Black);
	separateur.setPosition(hauteurFenetre, 0);
	
	sf::Font arial;
	if(!arial.loadFromFile("Ressources/arial.ttf"))
		cout << "Impossible de charger la police arial.ttf";
	
	sf::Text texteVitesse = compteurVitesse(nbPasse, arial, hauteurFenetre, largeurFenetre);
	
	sf::Text texteMode("Mode : Manuel", arial, 25);
	centrerTexte(texteMode, hauteurFenetre, largeurFenetre, 5, 5);
	
	string const t_tailleTas = "Taille du plus \n gros tas : ";
	sf::Text texteTailleTas("Taille du plus \n gros tas : 0", arial, 25);
	centrerTexte(texteTailleTas, hauteurFenetre, largeurFenetre, hauteurFenetre - 70, hauteurFenetre - 70);
	
	/* création de la fenêtre */
	sf::RenderWindow fenetre(sf::VideoMode(largeurFenetre, hauteurFenetre), "simulation termites");
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
						case sf::Keyboard::Return: // Il est conseillé d'utiliser Enter au lieu de Return, mais Enter n'existe pas dans version 2.4.2 (celle installée via apt sous linux)
							if(!passeAuto)
								for(int i = 0; i < nbPasse; i++){
									deplacement(g, tabT, maxBrindilles, grosTas);
									if(logTailleTas){
										tailleTas = tailleMaxTas(g, maxBrindilles, grosTas);
									}
								}
							break;
						case sf::Keyboard::Multiply: case sf::Keyboard::Up:
							nbPasse *= 2;
							texteVitesse = compteurVitesse(nbPasse, arial, hauteurFenetre, largeurFenetre);
							break;
						case sf::Keyboard::Slash: case sf::Keyboard::Down:
							if(nbPasse > 1){
								nbPasse /= 2;
								texteVitesse = compteurVitesse(nbPasse, arial, hauteurFenetre, largeurFenetre);
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
						case sf::Keyboard::L:
							logTailleTas = !logTailleTas;
							break;
						case sf::Keyboard::C:
							connexe = !connexe;
							if(connexe){
								if(!logTailleTas) logTailleTas = true;
							} else {
								initTabTasVide(maxBrindilles, grosTas);
							}
							break;
						default: break;
					}
				default: break;
			}
		}
		fenetre.clear(sf::Color(217, 160, 48));
		
		if(passeAuto)
			for(int i = 0; i < nbPasse; i++){
				if(connexe)
					deplacement(g, tabT, maxBrindilles, grosTas);
				else
					deplacement(g, tabT);
				if(logTailleTas){
					tailleTas = tailleMaxTas(g, maxBrindilles, grosTas);
				}
			}
		
		dessineGrille(g, tabT, tailleCase, fenetre, tabSprites, tabTextures);
		fenetre.draw(separateur);
		fenetre.draw(texteVitesse);
		fenetre.draw(texteMode);
		if(logTailleTas){
			texteTailleTas.setString(t_tailleTas + to_string(tailleTas));
			fenetre.draw(texteTailleTas);
		}
		
		fenetre.display();
	}
	return 0;
}