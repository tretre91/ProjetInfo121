struct Coord{
    int ligne, colonne;
};

enum Direction {NO, N, NE, E, SE, S, SO, O};

/** Constructeur du type Coord
 * @param [in] lig la coordonnée en abscisse
 * @param [in] col la coordonnée en ordonnée
 * @return une coordonnée initialisée à (lig, col)
 **/
Coord creeCoord(int lig, int col);

/** Permet d'obtenir la composante en x d'une Coord
 * @param [in] c la coordonnée dont on souhaite obtenir l'abscisse
 * @return l'abscisse de c
 **/
int getX(Coord c);

/** Permet d'obtenir la composante en y d'une Coord
 * @param [in] c la coordonnée dont on souhaite obtenir l'ordonnée
 * @return l'ordonnée de c
 **/
int getY(Coord c);

/** Vérifie si deux coordonées sont égales
 * @param [in] c1 la première coordonnée à comparer
 * @param [in] c2 la seconde coordonnée à comparer
 * @return true si les deux coordonnées sont égales
 **/
bool egalCoord(Coord c1, Coord c2);

/** Affiche une coordonnée
 * @param [in] c la coordonnée à afficher
 **/
void afficheCoord(Coord c);

/** Affiche une direction
 * @param [in] dir la direction à afficher
 **/
void afficheDirection(Direction dir);

/** Indique la direction située directement à droite
 * @param [in] dir la direction de base
 * @return la direction située à droite de dir
 **/
Direction aDroite(Direction dir);

/** Indique la direction située directement à gauche
 * @param [in] dir la direction de base
 * @return la direction située à gauche de dir
 **/
Direction aGauche(Direction dir);

/** Indique la coordonnée en face
 * @param [in] c une coordonnée
 * @param [in] dir une direction
 * @return la coordonnée obtenue lorsqu'on avance de 1 dans la direction dir
 *         à partir de c
 **/ 
Coord devantCoord(Coord c, Direction dir);