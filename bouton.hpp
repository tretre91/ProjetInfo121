#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#ifndef	DEF_WDIR
#define	DEF_WDIR

/** Permet de récuperer l'info sur le dossier de compilation
 * @return s le chemin vers le dossier où a eu lieu la compilation
 **/
std::string wdir();

#endif // DEF_WDIR

#ifndef DEF_BOUTON
#define DEF_BOUTON

class Bouton{
	public:
		/** Constructeur par défaut de la classe Bouton
		 * *Créé un bouton gris de taille 40*20 en position (0,0)
		 *  dont la légende est "bouton"
		 **/
		Bouton();
		
		/** Constructeur surchargé
		 * @param [in] size la taille du buton contenue dans un sf::Vector2f
		 * *Créé un bouton gris de taille size en position (0,0)
		 *  dont la légende est "bouton"
		 **/
		Bouton(sf::Vector2f const& size);
		/** Constructeur surchargé
		 * @param [in] size la taille du buton contenue dans un sf::Vector2f
		 * @param [in] color la couleur du bouton
		 * *Créé un bouton de couleur 'color' et de taille 'size' en position (0,0)
		 *  dont la légende est "bouton"
		 **/
		Bouton(sf::Vector2f const& size, sf::Color const& color);
		/** Constructeur surchargé
		 * @param [in] position la position du bouton dans la fenetre dans un sf::Vector2f
		 * @param [in] size la taille du buton contenue dans un sf::Vector2f
		 * *Créé un bouton gris et de taille 'size' en position 
		 *  (position.x, position.y) dont la légende est "bouton"
		 **/
		Bouton(sf::Vector2f const& position, sf::Vector2f const& size);
		/** Constructeur surchargé
		 * @param [in] position la position du bouton dans la fenetre dans un sf::Vector2f
		 * @param [in] size la taille du buton contenue dans un sf::Vector2f
		 * @param [in] color la couleur du bouton
		 * *Créé un bouton de couleur 'color' et de taille 'size' en position 
		 *  (position.x, position.y) dont la légende est "bouton"
		 **/
		Bouton(sf::Vector2f const& position, sf::Vector2f const& size, sf::Color const& color);
		
		/** Modifie la couleur du bouton (et eventuellement sa transparence)
		 * @param [in] color la nouvelle couleur du bouton
		 **/
		void setColor(sf::Color const& color);
		/** Modifie la couleur du bouton (et eventuellement sa transparence)
		 * @param [in] r,g,b les composantes rouge, vertes et bleues de la couleur voulue
		 * @param [in] alpha l'opacité du bouton
		 **/
		void setColor(int const& r, int const& g, int const& b, int alpha);
		/** Permet d'obtenir la couleur du bouton
		 * @return la couleur du bouton en tant que sf::Color
		 **/
		sf::Color getColor() const;
		/** Modifie la position du bouton
		 * @param [in] x la nouvelle coordonnée en x
		 * @param [in] y la nouvelle coordonnée en y
		 **/
		void setPosition(int const& x, int const& y);
		/** Modifie la position du bouton
		 * @param [in] pos un sf::Vector2f contenant les nouvelles coordonnées du bouton
		 **/
		void setPosition(sf::Vector2f const& pos);
		/** Permet d'obtenir la position actuelle du bouton
		 * @return la position du bouton dans un sf::Vector2f
		 **/
		sf::Vector2f getPosition() const;
		
		/** Modifie la taille du bouton
		 * @param [in] hauteur la nouvelle hauteur du bouton (en pixel)
		 * @param [in] largeur la nouvelle largeur du bouton (en pixel)
		 **/
		void setSize(int const& hauteur, int const& largeur);
		/** Modifie la taille du bouton
		 * @param [in] taille un sf::Vector2f contenant les nouvelles hauteur et largeur du bouton
		 **/
		void setSize(sf::Vector2f const& taille);
		/** Permet d'obtenir la taille du bouton
		 * @return les mesures du bouton contenues dan un sf::Vector2f
		 **/
		sf::Vector2f getSize() const;
		
		/** Modifie la légende du bouton
		 * @param [in] texte un string correspondant à la nouvelle légende
		 **/
		void setText(std::string const& texte);
		/** Modifie la légende du bouton
		 * @param [in] texte un sf::Text qui remplace celui du bouton
		 * *On peut modifier avec cette méthodes d'autres attributs de la légende
		 *  tels que la police, le style, la couleur, etc, il d'envoyer en paramètre
		 *  un sf::Text contenant les attributs souhaités
		 **/
		void setText(sf::Text const& texte);
		/** Permet d'obtenir le sf::Text correspondant à la légende du bouton
		 * @return le champ m_Texte
		 **/
		sf::Text getText() const;
		/** Permet d'obtenir le texte de la légende du bouton
		 * @return un string contenant la légende
		 **/
		std::string getString() const;
		/** Modifie la taille du texte de la légende
		 * @param taille la nouvelle taille du texte (en pixel)
		 **/
		void setTextSize(uint taille);
		
		/** Indique si une coordonée se trouve dans le bouton
		 * @param [in] x,y le couple de coordonnées à tester
		 * @return true si (x,y) est dans le bouton
		 **/
		bool contient(int const& x, int const& y) const;
		/** Indique si une coordonée se trouve dans le bouton
		 * @param [in] coord un sf::Vector2f contenant les coordonnées à tester
		 * @return true si (x,y) est dans le bouton
		 **/
		bool contient(sf::Vector2f const& coord) const;
		
		/** Permet de dessiner le bouton dans une sf::RenderWindow
		 * @param [in/out] window la fenêtre dans laquelle on vait dessiner le bouton
		 **/
		void dessiner(sf::RenderWindow &window);
	
	protected:
		sf::RectangleShape m_base;
		sf::Vector2f m_size;
		sf::Vector2f m_position;
		sf::Color m_color;
		sf::Font m_font;
		sf::Text m_text;
		
		/** Aligne la légende au milieu du bouton
		 **/
		void centerText();
};

#endif // DEF_BOUTON

#ifndef DEF_GRP_BOUTON
#define DEF_GRP_BOUTON

#endif // DEF_GRP_BOUTON