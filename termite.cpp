#include "termite.hpp"

void tabVide(tabTermites &T){
	T.taille = 0;
}

int tailleTableau(tabTermites T){
	return T.taille;
}

bool estPlein(tabTermites T){
	return T.taille == 2*TAILLE;
}

void creeTermite(tabTermites &T, Coord c){
	Termite nouv;
	nouv.numero = T.taille;
	nouv.position = c;
	nouv.direction = Direction(rand()%8);
	nouv.charge = false;
	
	T.tab[T.taille] = nouv;
	T.taille++;
}


Direction directionTermite(Termite t){
	return t.direction;
}

Coord devantTermite(Termite t){
	return devantCoord(t.position, t.direction);
}

bool porteBrindille(Termite t){
	return t.charge;
}

void tourneADroite(Termite &t){
	t.direction = aDroite(t.direction);
}

void tourneAGauche(Termite &t){
	t.direction = aGauche(t.direction);
}

void tourneAleat(Termite &t){
	t.direction = Direction(rand()%8);
}

bool laVoieEstLibre(Grille g, Termite t){
	return dansGrille(g, devantTermite(t)) && estVide(g, devantTermite(t));
}

bool brindilleEnFace(Grille g, Termite t){
	return contientBrindille(g, devantTermite(t));
}

bool pasEnferme(Grille g, Termite t){
	int casesVides = 0;
	for(int i = 0; i < 8; i++){
		tourneADroite(t);
		if(laVoieEstLibre(g, t))
			casesVides++;
	}
	return casesVides >= 2;
}

void avanceTermite(Grille &g, Termite &t){
	poseTermite(g, devantTermite(t), t.numero);
	enleveTermite(g, t.position);
	t.position = devantTermite(t);
}

void dechargeTermite(Grille &g, Termite &t){
	poseBrindille(g, devantTermite(t));
	t.charge = false;
}

void chargeTermite(Grille &g, Termite &t){
	enleveBrindille(g, devantTermite(t));
	t.charge = true;
}

void marcheAleatoire(Grille &g, Termite &t){
	int d = rand()%10;
	if(d == 9 && laVoieEstLibre(g, t))
		avanceTermite(g, t);
	else
		tourneAleat(t);
}