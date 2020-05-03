//les bibliothèques <SFML/Graphics.hpp>, <string> et <iostream> sont inclues dans "bouton.hpp"
#include <cstdlib>
#include "bouton.hpp"
#include "termite.hpp"
using namespace std;

const float DENSITE_TERMITE = 0.25;
const float DENSITE_BRINDILLE = 0.15;
const int NB_TEXTURES = 5;

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
	
	if(!tabTextures[0].loadFromFile(wdir()+"Ressources/termite_n.png")){ // texture de termite droit
		cout << "Echec du chargement de la texture termite_droit" << endl;
	}
	
	if(!tabTextures[1].loadFromFile(wdir()+"Ressources/termite_no.png")){ // texture de termite penché (en diagonale)
		cout << "Echec du chargement de la texture termite_penche" << endl;
	}
	
	if(!tabTextures[2].loadFromFile(wdir()+"Ressources/brindille.png")){ // texture de brindille
		cout << "Echec du chargement de la texture brindille" << endl;
	}
	
	if(!tabTextures[3].loadFromFile(wdir()+"Ressources/termite_charge_n.png")){ // texture de termite droit qui porte une brindille
		cout << "Echec du chargement de la texture termite_charge_droit" << endl;
	}
	
	if(!tabTextures[5].loadFromFile(wdir()+"Ressources/termite_charge_no.png")){ // texture de termite penché qui porte une brindille
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
	sf::Sprite grilleSprite[TAILLE][TAILLE];
	copieGrille(g, tabT, tailleCase, grilleSprite, tabTextures);
	
	/* Génération des autres objets (bordures, déco, boutons ...) */
	int tailleFenetre = tailleCase*TAILLE;
	sf::Color const gris(130, 130, 130);
	
	sf::RectangleShape separateur(sf::Vector2f(5, tailleFenetre));
	separateur.setFillColor(sf::Color::Black);
	separateur.setPosition(tailleFenetre, 0);
	
	Bouton passe(sf::Vector2f(tailleFenetre+50, 50), sf::Vector2f(100, 50), gris);
	passe.setText("Passe");
	passe.setTextSize(30);
	
	Bouton bouton;
	bouton.setPosition(tailleFenetre+50, 200);
	
	/* ctéation de la fenêtre */
	sf::RenderWindow fenetre(sf::VideoMode(tailleCase*TAILLE+205, tailleCase*TAILLE), "simulation termites");
	fenetre.setVerticalSyncEnabled(false);
	fenetre.setFramerateLimit(60);
	
	
	while(fenetre.isOpen()){
		sf::Event event;
		while(fenetre.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
					fenetre.close();
					break;
				case sf::Event::MouseButtonPressed:
					if(event.mouseButton.button == sf::Mouse::Left)
						if(passe.contient(event.mouseButton.x, event.mouseButton.y))
							bouton.setSize(100, 50);
					break;
				default: break;
			}
		}
		fenetre.clear(sf::Color(217, 160, 48));
		
		for(int i = 0; i < TAILLE; i++)
			for(int j = 0; j < TAILLE; j++)
				fenetre.draw(grilleSprite[i][j]);
		
		fenetre.draw(separateur);
		passe.dessiner(fenetre);
		bouton.dessiner(fenetre);
		
		fenetre.display();
	}
	return 0;
}