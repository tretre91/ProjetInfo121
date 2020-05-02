#include "coord.hpp"
#include <iostream>
using namespace std;

Coord creeCoord(int lig, int col){
    return {lig, col};
}

int getX(Coord c){
    return c.ligne;
}

int getY(Coord c){
    return c.colonne;
}

bool egalCoord(Coord c1, Coord c2){
    return c1.ligne == c2.ligne and c1.colonne == c2.colonne;
}

void afficheCoord(Coord c){
    cout << "(" << c.ligne << "," << c.colonne << ")";
}

void afficheDirection(Direction dir){
    switch(dir){
        case 0: cout << "nord-ouest"; break;
        case 1: cout << "nord"; break;
        case 2: cout << "nord-est"; break;
        case 3: cout << "est"; break;
        case 4: cout << "sud-est"; break;
        case 5: cout << "sud"; break;
        case 6: cout << "sud-ouest"; break;
        case 7: cout << "ouest"; break;
    }
}

Direction aDroite(Direction dir){
    if(dir == 7)
        return Direction(0);
    return Direction(dir + 1);
}

Direction aGauche(Direction dir){
    if(dir == 0)
        return Direction(7);
    return Direction(dir - 1);
}

Coord devantCoord(Coord c, Direction dir){
    if(dir <= 2)
        c.ligne--;
    if(dir >= 4 and dir <= 6)
        c.ligne++;
    if(dir == 0 or dir >= 6)
        c.colonne--;
    if(dir >= 2 and dir <= 4)
        c.colonne++;
    return c;
}