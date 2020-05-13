#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include "termite.hpp"
using namespace std;

const float DENSITE_TERMITE = 0.25;
const float DENSITE_BRINDILLE = 0.2;
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


void afficheGrille(Grille g, tabTermites T){
    system("clear");
    int b = 0;
    for(int i = 0; i < TAILLE; i++){
        for(int j = 0; j < TAILLE; j++){
            if(contientBrindille(g, {i,j})){
				b++;
                cout << "*";
			}
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
	cout << b << endl;
}

void initGrille(Grille &g, tabTermites &T){
    initialiseGrilleVide(g);
    for(int i = 0; i < TAILLE; i++)
        for(int j = 0; j < TAILLE; j++){
            float nb = rand()%10;
            nb /= 10;
            if(nb < DENSITE_BRINDILLE){
                poseBrindille(g, {i,j});
            } else if(nb < DENSITE_TERMITE){
                if(!estPlein(T)){
                    creeTermite(T, {i,j});
                    poseTermite(g, {i,j}, tailleTableau(T));
                }
            }
        }
}

void deplacement(Grille &g, tabTermites &T){
	for(int i = 0; i < tailleTableau(T); i++){
		modifierSablier(T.tab[i]);
		if(sablier(T.tab[i]) == 0 && brindilleEnFace(g, T.tab[i])){
			if(!porteBrindille(T.tab[i]))
				chargeTermite(g, T.tab[i]);
			else if(porteBrindille(T.tab[i]) && pasEnferme(g, T.tab[i])){
				while(!laVoieEstLibre(g, T.tab[i]))
					tourneADroite(T.tab[i]);
				dechargeTermite(g, T.tab[i]);
			}
			else
				marcheAleatoire(g, T.tab[i]);
		} else {
			if(murEnFace(g, T.tab[i]))
				T.tab[i].tournerSurPlace = true;
			marcheAleatoire(g, T.tab[i]);
		}
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
    initGrille(g, tabT);
	int nbPasse = 1;
	
	/* Génération des autres objets (bordures, déco, boutons ...) */
	int const tailleFenetre = tailleCase*TAILLE;
	
	sf::RectangleShape separateur(sf::Vector2f(5, tailleFenetre));
	separateur.setFillColor(sf::Color::Black);
	separateur.setPosition(tailleFenetre, 0);
	
	
	
	/* ctéation de la fenêtre */
	sf::RenderWindow fenetre(sf::VideoMode(tailleFenetre + 205, tailleFenetre), "simulation termites", 5);
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
							for(int i = 0; i < nbPasse; i++)
								deplacement(g, tabT);
							break;
						case sf::Keyboard::Multiply:
						case sf::Keyboard::Up:
							if(nbPasse < 1000)
								nbPasse *= 10;
							break;
						case sf::Keyboard::Slash:
						case sf::Keyboard::Down:
							if(nbPasse > 1)
								nbPasse /= 10;
							break;
						default: break;
					}
				default: break;
			}
		}
		fenetre.clear(sf::Color(217, 160, 48));
		
		dessineGrille(g, tabT, tailleCase, fenetre, tabSprites, tabTextures);
		fenetre.draw(separateur);
		
		fenetre.display();
	}
	return 0;
}