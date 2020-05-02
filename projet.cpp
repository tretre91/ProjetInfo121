#include "termite.hpp"
#include <iostream>
#include <cstdlib>
using  namespace std;

const float DENSITE_TERMITE = 0.25;
const float DENSITE_BRINDILLE = 0.2;

void afficheGrille(Grille g, tabTermites T){
    system("clear");
    
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

int main(){
    srand(time(0));
    tabTermites tabT;
    tabVide(tabT);
    Grille g;
    initGrille(g, tabT);
    afficheGrille(g, tabT);
    return 0;
}