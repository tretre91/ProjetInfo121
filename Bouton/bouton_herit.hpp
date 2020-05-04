#include "bouton.hpp"

#ifndef DEF_BOUTON_TEXTE
#define DEF_BOUTON_TEXTE

class BoutonTexte : public Bouton{
	public:
		BoutonTexte();
		
		BoutonTexte(sf::Vector2f const& size);
		BoutonTexte(std::string const& texte);
		BoutonTexte(sf::Text const& texte);
		BoutonTexte(sf::Vector2f const& position, std::string const& texte);
		BoutonTexte(sf::Vector2f const& position, sf::Text const& texte);
		BoutonTexte(sf::Vector2f const& position, sf::Vector2f const& size, std::string const& texte);
		BoutonTexte(sf::Vector2f const& position, sf::Vector2f const& size, sf::Text const& texte);
		
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
		
		/** Modifie la taille du texte de la légende
		 * @param [in] taille la nouvelle taille du texte (en pixel)
		 **/
		void setTextSize(uint taille);
		
		/** Modifie la police du texte de la légende
		 * @param [in] font la nouvelle police à utiliser
		 **/
		void setFont(sf::Font const& font);
		
		/** Permet de définir si la légende est écrite en gras
		 * @param [in] bold: un booléen qui indique si le texte doit être en gras
		 **/
		void setBold(bool bold);
		
		/** Permet de définir si la légende est écrite en italique
		 * @param [in] italic: un booléen qui indique si le texte doit être en italique
		 **/
		void setItalic(bool italic);
		
		/** Permet de définir si la légende est soulignée
		 * @param [in] underlined: un booléen qui indique si le texte doit être souligné
		 **/
		void setUnderlined(bool underlined);
		
		/** Permet de définir si la légende est barrée
		 * @param [in] strikeThrough: un booléen qui indique si le texte doit être barré
		 **/
		void setStrikeThrough(bool strikeThrough);
		
		/** Permet d'obtenir le sf::Text correspondant à la légende du bouton
		 * @return un sf::Text correspondant à celui du bouton
		 **/
		sf::Text getText() const;
		
		/** Permet d'obtenir le texte de la légende du bouton
		 * @return un string contenant la légende
		 **/
		std::string getString() const;
		
		/** Permet de dessiner le bouton dans une sf::RenderWindow
		 * @param [in/out] window la fenêtre dans laquelle on vait dessiner le bouton
		 **/
		void dessiner(sf::RenderWindow &window);
		
	protected:
		sf::Font m_font;
		sf::Text m_text;
		bool m_style[4];
		
		/** Vérifie si texte ne dépasse pas du bouton **/
		bool fitText() const;
		/** adapte la taille du bouton pour contenir la légende **/
		void adaptText();
		/** Aligne la légende au milieu du bouton **/
		void centerText();
		/** Modifie les booléens contenus dans m_style. Utilisée uniquement dans la méthode initStyle() **/
		void modifStyle(bool bold, bool italic, bool underlined, bool strikeThrough);
		/** Enregistre la donnée sur le style du sf::Text de la légende **/
		void initStyle();
};

#endif

#ifndef DEF_BOUTON_IMAGE
#define DEF_BOUTON_IMAGE

// class BoutonImage : public Bouton{
	// public:
		// BoutonImage();
		// BoutonImage(sf::Texture &texture);
		// BoutonImage(sf::Vector2f const& size);
		// BoutonImage(sf::Vector2f const& size, sf::Texture &texture);
	// protected:
		// sf::Texture m_texture;
		// sf::Sprite m_sprite;
// };

#endif // DEF_BOUTON_IMAGE