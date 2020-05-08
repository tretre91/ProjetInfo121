//les bibliothèques <SFML/Graphics.hpp>, <string> et <iostream> sont inclues dans "bouton.hpp"
#include <cstdlib>
#include "Bouton/bouton_herit.hpp"
#include "Bouton/bouton.hpp"
#include "termite.hpp"
using namespace std;

const float DENSITE_TERMITE = 0.25;
const float DENSITE_BRINDILLE = 0.15;
const int NB_TEXTURES = 8;

/** Permet de récuperer le chemin du dossier du fichier
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

/** Permet de charger les textures nécessaires à la simulation (grille et ui)
 * @param [out] tabTextures: le tableau de sf::Texture qui contient toutes les textures
 * @param [in] path: le chemin vers le dossier où a eu lieu la compilation
 **/
void initTextures(sf::Texture tabTextures[NB_TEXTURES], string const& path){
	if(!tabTextures[0].loadFromFile(path + "termite_n.png")){ // texture de termite droit
		cout << "Echec du chargement de la texture termite_droit" << endl;
	}
	if(!tabTextures[1].loadFromFile(path + "termite_no.png")){ // texture de termite penché (en diagonale)
		cout << "Echec du chargement de la texture termite_penche" << endl;
	}
	if(!tabTextures[2].loadFromFile(path + "brindille.png")){ // texture de brindille
		cout << "Echec du chargement de la texture brindille" << endl;
	}
	if(!tabTextures[3].loadFromFile(path + "termite_charge_n.png")){ // texture de termite droit qui porte une brindille
		cout << "Echec du chargement de la texture termite_charge_droit" << endl;
	}
	if(!tabTextures[4].loadFromFile(path + "termite_charge_no.png")){ // texture de termite penché qui porte une brindille
		cout << "Echec du chargement de la texture termite_charge_penche" << endl;
	}
	if(!tabTextures[5].loadFromFile(path + "play.png")){ // texture de logo play
		cout << "Echec du chargement de la texture play" << endl;
	}
	if(!tabTextures[6].loadFromFile(path + "pause.png")){ // texture de logo pause
		cout << "Echec du chargement de la texture pause" << endl;
	}
	if(!tabTextures[7].loadFromFile(path + "rewind.png")){ // texture de logo avance rapide
		cout << "Echec du chargement de la texture rewind" << endl;
	}
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
void rotation(sf::Sprite &s, int angle, int tailleCase = -1){
	sf::Vector2i dimensionsCase;
	if(tailleCase == -1)
		dimensionsCase = sf::Vector2i(s.getGlobalBounds().width, s.getGlobalBounds().height);
	else
		dimensionsCase = sf::Vector2i(tailleCase, tailleCase);
	sf::Vector2f scale = s.getScale();
	sf::Vector2f pos = s.getPosition();
	s.setRotation(angle);
	switch(angle){
		case 90: s.setPosition(pos.x + scale.x * dimensionsCase.y, pos.y); break;
		case 180: s.setPosition(pos.x + scale.x * dimensionsCase.x, pos.y + scale.y * dimensionsCase.y); break;
		case 270: s.setPosition(pos.x, pos.y + scale.y * dimensionsCase.x); break;
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
	string const cheminRessources = wdir()+"Ressources/";
	
	/* Chargement des textures */
	sf::Texture tabTextures[NB_TEXTURES];
	initTextures(tabTextures, cheminRessources);
	
	/* determination de la taille d'une case (en pixel) */
	int tailleCase = initTaileCase();
	
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
	
	sf::RectangleShape separateur(sf::Vector2f(5, tailleFenetre));
	separateur.setFillColor(sf::Color::Black);
	separateur.setPosition(tailleFenetre, 0);
	
	BoutonTexte passe(sf::Vector2f(tailleFenetre+50, 50), sf::Vector2f(100, 50), "Passe");
	passe.setTextSize(30);
	passe.setBold(true);
	
	sf::Sprite play_sprite(tabTextures[5]);
	bool isPlay = true;
	sf::Sprite pause_sprite(tabTextures[6]);
	sf::Sprite vitessePlus_sprite(tabTextures[7]);
	sf::Sprite vitesseMoins_sprite(tabTextures[7]);
	sf::Sprite test(tabTextures[7]);
	
	BoutonImage play(play_sprite), vitessePlus(vitessePlus_sprite), vitesseMoins(vitesseMoins_sprite);
	play.setPosition(tailleFenetre + (200 - play.getSize().x)/2, 400);
	vitesseMoins.setPosition(play.getPosition().x - vitesseMoins.getSize().x, play.getPosition().y);
	vitessePlus.setPosition(play.getPosition().x + play.getSize().x, play.getPosition().y);
	
	vitesseMoins.setRotation(90.f);
	
	/* ctéation de la fenêtre */
	sf::RenderWindow fenetre(sf::VideoMode(tailleCase*TAILLE+205, tailleCase*TAILLE), "simulation termites", 5);
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
					if(passe.contient(event.mouseButton.x, event.mouseButton.y))
						switch(event.mouseButton.button){
							case sf::Mouse::Left:
								rotation(test, 180);
								break;
							case sf::Mouse::Right:
								passe.setText("Clic!");
								passe.setUnderlined(false);
								passe.setStrikeThrough(true);
								passe.setPosition(tailleFenetre+50, 100);
								break;
							default: break;
						}
					else if(play.contient(event.mouseButton.x, event.mouseButton.y))
						if(event.mouseButton.button == sf::Mouse::Left){
							if(isPlay)
								play.setIcon(pause_sprite);
							else
								play.setIcon(play_sprite);
							isPlay = !isPlay;
						}
					break;
				default: break;
			}
		}
		fenetre.clear(sf::Color(217, 160, 48));
		
		for(int i = 0; i < TAILLE; i++)
			for(int j = 0; j < TAILLE; j++)
				fenetre.draw(grilleSprite[i][j]);
		
		fenetre.draw(separateur);
		fenetre.draw(test);
		passe.dessiner(fenetre);
		play.dessiner(fenetre);
		vitesseMoins.dessiner(fenetre);
		vitessePlus.dessiner(fenetre);
		
		fenetre.display();
	}
	return 0;
}