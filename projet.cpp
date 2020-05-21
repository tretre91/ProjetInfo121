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
	char a;
	int nbPasse = 1;
	int modif = 1;
	while(true){
		if(modif > 0)
			modif--;
		a = getchar();
		switch(a){
			case 'q': return;
			case '*': nbPasse *= 2; modif = 2; break;
			case '/': if(nbPasse > 1) nbPasse /= 2; modif = 2; break;
			default: break;
		}
		
		if(!modif){
			for(int i = 0; i < nbPasse; i++)
				deplacement(g, T);
			afficheGrille(g, T);
		}
		
		cout << "Vitesse x" << nbPasse << endl;
	}
}

int main(){
    srand(time(0));
    tabTermites tabT;
    tabVide(tabT);
    Grille g;
    initGrille(g, tabT);
    afficheGrille(g, tabT);
	
	simulation(g, tabT);
    return 0;
}