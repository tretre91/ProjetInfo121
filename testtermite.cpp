#include "termite.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

#define ASSERT(test) if (!(test)) std::cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << std::endl

void testTabTermites(){
    Grille g;
    initialiseGrilleVide(g);
    
    tabTermites t;
    tabVide(t);
    int x, y;
    for(int i = 0; i < 2*TAILLE; i++){
        do{
            x = rand()%TAILLE;
            y = rand()%TAILLE;
        }while(!estVide(g, {x, y}));
        creeTermite(t, {x, y});
    }
    
    ASSERT(estPlein(t));
    
    for(int i = 0; i < 2*TAILLE; i++){
        ASSERT(!porteBrindille(t.tab[i]));
        if(laVoieEstLibre(g, t.tab[i])){
            poseBrindille(g, devantTermite(t.tab[i]));
            chargeTermite(g, t.tab[i]);
            ASSERT(porteBrindille(t.tab[i]));
            dechargeTermite(g, t.tab[i]);
        }
    }
    for(int i = 0; i < 2*TAILLE; i++)
        ASSERT(!porteBrindille(t.tab[i]));
}

int main(){
    srand(time(0));
    testTabTermites();
    return 0;
}