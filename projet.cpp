#include "termite.hpp"
#include <iostream>
#include <cstdlib>
using  namespace std;

const float DENSITE_TERMITE = 0.25;
const float DENSITE_BRINDILLE = 0.2;

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
		if(sablier(T.tab[i]) == 0){
			if(brindilleEnFace(g, T.tab[i]) && !porteBrindille(T.tab[i]))
				chargeTermite(g, T.tab[i]);
			else if(porteBrindille(T.tab[i]) && pasEnferme(g, T.tab[i]) && laVoieEstLibre(g, T.tab[i]))
				dechargeTermite(g, T.tab[i]);
			else
				marcheAleatoire(g, T.tab[i]);
		} else {
			marcheAleatoire(g, T.tab[i]);
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
	
	char a;
	while(true){
		a = getchar();
		if(a == 'q')
			break;
		deplacement(g, tabT);
		afficheGrille(g, tabT);
	}
    return 0;
}