#include "grille.hpp"
#include <iostream>
using namespace std;

#define ASSERT(test) if (!(test)) std::cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << std::endl

void initialiseCaseVide(Case &c){
    c.contenu = -1;
}

void initialiseGrilleVide(Grille &g){
    for(int i = 0; i < TAILLE; i++)
        for(int j = 0; j <TAILLE; j++)
			initialiseCaseVide(g.t[i][j]);
}

bool estVide(Grille g, Coord c){
    return g.t[getX(c)][getY(c)].contenu == -1;
}

bool dansGrille(Grille g, Coord c){
    int x = getX(c);
    int y = getY(c);
    return x >= 0 && x < TAILLE && y >= 0 && y < TAILLE;
}

bool contientBrindille(Grille g, Coord c){
    return dansGrille(g, c) && g.t[getX(c)][getY(c)].contenu == -2;
}

int numeroTermite(Grille g, Coord c){
    if(g.t[getX(c)][getY(c)].contenu < 0)
        return -1;
    return g.t[getX(c)][getY(c)].contenu;
}

void poseBrindille(Grille &g, Coord c){
    ASSERT(dansGrille(g, c) && estVide(g, c));
    if(dansGrille(g, c) && estVide(g, c))
        g.t[getX(c)][getY(c)].contenu = -2;
}

void enleveBrindille(Grille &g, Coord c){
    ASSERT(dansGrille(g, c) && contientBrindille(g, c));
    if(dansGrille(g, c) && contientBrindille(g, c))
        g.t[getX(c)][getY(c)].contenu = -1;
}

void poseTermite(Grille &g, Coord c, int numTermite){
    ASSERT(dansGrille(g, c) && estVide(g, c) && numTermite >= 0);
    if(dansGrille(g, c) && estVide(g, c) && numTermite >= 0)
        g.t[getX(c)][getY(c)].contenu = numTermite;
}

void enleveTermite(Grille &g, Coord c){
    ASSERT(dansGrille(g, c) && numeroTermite(g, c) != -1);
    if(dansGrille(g, c) && numeroTermite(g, c) != -1)
        g.t[getX(c)][getY(c)].contenu = -1;
}