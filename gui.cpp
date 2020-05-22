#include "gui.hpp"
using namespace std;

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

int initTailleCase(){
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
    bool dessin = false; // indique si on doit afficher qqchose sur la case correspondante
    
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

sf::Text compteurVitesse(int vitesse, sf::Font const& police, int const hauteurFenetre, int const largeurFenetre){
    sf::Text texteVitesse("Vitesse : x" + to_string(vitesse), police, 25);
    centrerTexte(texteVitesse, hauteurFenetre, largeurFenetre, 0, hauteurFenetre); // centre le texte au milieu (verticalement) à droite
    return texteVitesse;
}