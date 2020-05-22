#include "simulation.hpp"
#include <iostream>
#include <cstdlib>
using  namespace std;

void afficheGrille(Grille g, tabTermites T){
    system("clear");
    for(int i = 0; i < TAILLE; i++){
        for(int j = 0; j < TAILLE; j++){
            if(contientBrindille(g, {i,j})){
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
}

void simulation(Grille &g, tabTermites &T){
	int nbPasse = 1;
	string a;
	bool passe;
	
	const int maxBrindilles = initGrille(g, T);
	afficheGrille(g, T);
    Coord grosTas[maxBrindilles];
	initTabTasVide(maxBrindilles, grosTas);
	int tailleTas = 0;
	bool connexe = false;
	
	while(true){
		passe = true;
		getline(cin, a);
		for(char i: a)
		switch(i){
			case 'q': return;
			case '*': nbPasse *= 2; passe = false; break;
			case '/': if(nbPasse > 1) nbPasse /= 2; passe = false; break;
			case 'c': connexe = !connexe; passe = false; break;
			default: break;
		}
		
		if(passe){
			for(int i = 0; i < nbPasse; i++){
				tailleTas = tailleMaxTas(g, maxBrindilles, grosTas);
				if(connexe)
					deplacement(g, T, maxBrindilles, grosTas);
				else
					deplacement(g, T);
			}
		}
		afficheGrille(g, T);
		cout << "Vitesse x" << nbPasse << endl;
		cout << "Taille du plus gros tas :" << tailleTas << endl;
	}
}

int main(){
    srand(time(0));
    tabTermites tabT;
    tabVide(tabT);
    Grille g;
    simulation(g, tabT);
    return 0;
}