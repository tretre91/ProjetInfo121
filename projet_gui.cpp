#include "gui.hpp"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
	/* Chargement des textures */
	sf::Texture tabTextures[NB_TEXTURES];
	sf::Sprite tabSprites[NB_TEXTURES];
	initTextures(tabTextures, tabSprites);
	
	/* determination de la taille d'une case (en pixel) */
	const int tailleCase = initTailleCase();
	const int hauteurFenetre = tailleCase*TAILLE;
	const int largeurFenetre = hauteurFenetre + 250;
	
	srand(time(0));
	
	/* création de la fenêtre */
	sf::RenderWindow window(sf::VideoMode(largeurFenetre, hauteurFenetre), "simulation termites");
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(60);
	
	while(simulation(tabTextures, tabSprites, tailleCase, hauteurFenetre, largeurFenetre, window)){}
	
	return 0;
}