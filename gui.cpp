#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include "termite.hpp"
using namespace std;

const float DENSITE_TERMITE = 0.25;
const float DENSITE_BRINDILLE = 0.15;
const int NB_TEXTURES = 5;

/** Permet de récuperer l'info sur le dossier de compilation
 * @return s le chemin vers le dossier où a eu lieu la compilation
 **/
string wdir(){
	string s = __FILE__;
	for(int i = s.size()-1; i >= 0; i--)
		if(s[i] == '/'){
			s.erase(i+1, s.size());
			break;
		}
	return s;
}

/** Permet de faire tourner un sprite de 90,180 ou 270°
 * @param s le sprite à modifier
 * @param angle l'angle souhaité por le sprite
 **/
void rotation(sf::Sprite &s, int angle, int tailleCase){
	sf::Vector2f scale = s.getScale();
	sf::Vector2f pos = s.getPosition();
	s.setRotation(angle);
	switch(angle){
		case 90: s.setPosition(pos.x + scale.x*tailleCase, pos.y); break;
		case 180: s.setPosition(pos.x + scale.x*tailleCase, pos.y + scale.y*tailleCase); break;
		case 270: s.setPosition(pos.x, pos.y + scale.y*tailleCase); break;
		default: break;
	}
}
	

void copieGrille(Grille g, tabTermites T, int tailleCase, sf::Sprite tab[TAILLE][TAILLE], sf::Texture textures[NB_TEXTURES]){
	for(int i = 0; i < TAILLE; i++)
		for(int j = 0; j < TAILLE; j++){
			tab[i][j].setPosition(tailleCase*j, tailleCase*i);
			if(contientBrindille(g, {i,j})){
				tab[i][j].setTexture(textures[2]);
			} else if(numeroTermite(g, {i,j}) != -1){
				switch(directionTermite(T.tab[numeroTermite(g, {i,j})])){
					case NO:tab[i][j].setTexture(textures[1]);
							break;
					case  N:tab[i][j].setTexture(textures[0]);
							break;
					case NE:tab[i][j].setTexture(textures[1]);
							rotation(tab[i][j], 90, tailleCase);
							break;
					case  E:tab[i][j].setTexture(textures[0]);
							rotation(tab[i][j], 90, tailleCase);
							break;
					case SE:tab[i][j].setTexture(textures[1]);
							rotation(tab[i][j], 180, tailleCase);
							break;
					case  S:tab[i][j].setTexture(textures[0]);
							rotation(tab[i][j], 180, tailleCase);
							break;
					case SO:tab[i][j].setTexture(textures[1]);
							rotation(tab[i][j], 270, tailleCase);
							break;
					case  O:tab[i][j].setTexture(textures[0]);
							rotation(tab[i][j], 270, tailleCase);
							break;
				}
			}
			tab[i][j].setScale(tailleCase/30., tailleCase/30.);
		}
}


void initGrille(Grille &g, tabTermites &T){
    initialiseGrilleVide(g);
    for(int i = 0; i < TAILLE; i++){
        for(int j = 0; j < TAILLE; j++){
            float nb = rand()%10;
            nb /= 10;
            if(nb < DENSITE_BRINDILLE){
                poseBrindille(g, {i,j});
            }
		}
	}
	int x, y;
	
	while(!estPlein(T)){
		do{
			x = rand()%TAILLE;
			y = rand()%TAILLE;
		}while(!estVide(g, {x,y}));
		creeTermite(T, {x,y});
		poseTermite(g, {x,y}, tailleTableau(T));
	}
}

void afficheGrille(Grille g, tabTermites T){    
    for(int i = 0; i < TAILLE; i++){
        for(int j = 0; j < TAILLE; j++){
            if(contientBrindille(g, {i,j}))
                cout << "*";
            else if(numeroTermite(g, {i,j}) != -1)
                switch(directionTermite(T.tab[numeroTermite(g, {i,j})])){
                    case N: case S: cout << "|"; break;
                    case NE: case SO: cout << "/"; break;
                    case E: case O: cout << "-"; break;
                    case SE: case NO: cout << "\\"; break;
                }
            else 
                cout << " ";
            cout << " ";
        }
        cout << endl;
    }
}

int main(){
	/* Chargement des textures */
	sf::Texture tabTextures[NB_TEXTURES];
	
	// texture de termite droit
	if(!tabTextures[0].loadFromFile(wdir()+"Images/termite_n.png")){
		cout << "Echec du chargement de la texture termite_droit" << endl;
	}
	// texture de termite penché (en diagonale)
	if(!tabTextures[1].loadFromFile(wdir()+"Images/termite_no.png")){
		cout << "Echec du chargement de la texture termite_penche" << endl;
	}
	// texture de brindille
	if(!tabTextures[2].loadFromFile(wdir()+"Images/brindille.png")){
		cout << "Echec du chargement de la texture brindille" << endl;
	}
	// texture de termite droit qui porte une brindille
	if(!tabTextures[3].loadFromFile(wdir()+"Images/termite_charge_n.png")){
		cout << "Echec du chargement de la texture termite_charge_droit" << endl;
	}
	// texture de termite penché qui porte une brindille
	if(!tabTextures[5].loadFromFile(wdir()+"Images/termite_charge_no.png")){
		cout << "Echec du chargement de la texture termite_charge_penche" << endl;
	}
	/* Fin du chargement des textures */
	
	/* determination de la taille d'une case (en pixel) */
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
	
	/* initialisation des grilles et tableaux de la simulation */
	srand(time(0));
    tabTermites tabT;
    tabVide(tabT);
    Grille g;
    initGrille(g, tabT);
	// afficheGrille(g, tabT);
	sf::Sprite grilleSprite[TAILLE][TAILLE];
	copieGrille(g, tabT, tailleCase, grilleSprite, tabTextures);
	
	/* ctéation de la fenêtre */
	sf::RenderWindow fenetre(sf::VideoMode(tailleCase*TAILLE, tailleCase*TAILLE), "simulation termites");
	fenetre.setVerticalSyncEnabled(false);
	fenetre.setFramerateLimit(60);
	
	
	while(fenetre.isOpen()){
		sf::Event event;
		while(fenetre.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				fenetre.close();
		}
		fenetre.clear(sf::Color(217, 160, 48));
		
		for(int i = 0; i < TAILLE; i++)
			for(int j = 0; j < TAILLE; j++)
				fenetre.draw(grilleSprite[i][j]);
		
		fenetre.display();
	}
	return 0;
}