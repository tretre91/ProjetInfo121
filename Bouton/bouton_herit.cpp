#include "bouton_herit.hpp"
using namespace std;

////////////////////////////////////////////////////////////////////////////////
////////////////////// Fonctions de la classe BoutonTexte //////////////////////
////////////////////////////////////////////////////////////////////////////////

BoutonTexte::BoutonTexte() : Bouton(){
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text("Bouton", m_font, 20);
	this->initStyle();
	this->adaptText();
}

BoutonTexte::BoutonTexte(sf::Vector2f const& size) : Bouton(size){
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text("Bouton", m_font, 20);
	this->initStyle();
	this->adaptText();
}

BoutonTexte::BoutonTexte(std::string const& texte) : Bouton(){
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text(texte, m_font, 20);
	this->initStyle();
	if(fitText())
		this->centerText();
	else
		this->adaptText();
}

BoutonTexte::BoutonTexte(sf::Text const& texte) : Bouton(){
	m_text = texte;
	this->initStyle();
	if(fitText())
		this->centerText();
	else
		this->adaptText();
}

BoutonTexte::BoutonTexte(sf::Vector2f const& position, std::string const& texte) : Bouton(position, sf::Vector2f(5,5)){
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text(texte, m_font, 20);
	this->initStyle();
	this->adaptText();
}

BoutonTexte::BoutonTexte(sf::Vector2f const& position, sf::Text const& texte) : Bouton(position, sf::Vector2f(5,5)){
	m_text = texte;
	this->initStyle();
	this->adaptText();
}

BoutonTexte::BoutonTexte(sf::Vector2f const& position, sf::Vector2f const& size, std::string const& texte) : Bouton(position, size){
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text(texte, m_font, 20);
	this->initStyle();
	this->adaptText();
}
	
BoutonTexte::BoutonTexte(sf::Vector2f const& position, sf::Vector2f const& size, sf::Text const& texte) : Bouton(position, size){
	m_text = texte;
	this->initStyle();
	this->adaptText();
}

/* Modification du texte du bouton */

void BoutonTexte::setText(string const& texte){
	m_text.setString(texte);
	this->adaptText();
}

void BoutonTexte::setText(sf::Text const& texte){
	m_text = texte;
	this->adaptText();
}

void BoutonTexte::setFont(sf::Font const& font){
	m_text.setFont(font);
	this->adaptText();
}

void BoutonTexte::setTextSize(uint taille){
	m_text.setCharacterSize(taille);
	this->adaptText();
}

void BoutonTexte::setBold(bool bold){
	if(bold){
		if(!m_style[0]){
			m_text.setStyle(m_text.getStyle() + sf::Text::Bold);
			m_style[0] = true;
		}
	}else{
		if(m_style[0]){
			m_text.setStyle(m_text.getStyle() - sf::Text::Bold);
			m_style[0] = false;
		}
	}
	this->adaptText();
}

void BoutonTexte::setItalic(bool italic){
	if(italic){
		if(!m_style[1]){
			m_text.setStyle(m_text.getStyle() + sf::Text::Italic);
			m_style[1] = true;
		}
	}else{
		if(m_style[1]){
			m_text.setStyle(m_text.getStyle() - sf::Text::Italic);
			m_style[1] = false;
		}
	}
	this->adaptText();
}

void BoutonTexte::setUnderlined(bool underlined){
	if(underlined){
		if(!m_style[2]){
			m_text.setStyle(m_text.getStyle() + sf::Text::Underlined);
			m_style[2] = true;
		}
	}else{
		if(m_style[2]){
			m_text.setStyle(m_text.getStyle() - sf::Text::Underlined);
			m_style[2] = false;
		}
	}
	this->adaptText();
}

void BoutonTexte::setStrikeThrough(bool strikeThrough){
	if(strikeThrough){
		if(!m_style[3]){
			m_text.setStyle(m_text.getStyle() + sf::Text::StrikeThrough);
			m_style[3] = true;
		}
	}else{
		if(m_style[3]){
			m_text.setStyle(m_text.getStyle() - sf::Text::StrikeThrough);
			m_style[3] = false;
		}
	}
	this->adaptText();
}

sf::Text BoutonTexte::getText() const{
	return m_text;
}

std::string BoutonTexte::getString() const{
	return m_text.getString();
}

/* Dessin du bouton */

void BoutonTexte::dessiner(sf::RenderWindow &window){
	window.draw(m_base);
	window.draw(m_text);
}	

/* Méthodes protégées */

bool BoutonTexte::fitText() const{
	return this->getSize().x >= m_text.getGlobalBounds().width && this->getSize().y >= m_text.getGlobalBounds().height;
}

void BoutonTexte::adaptText(){
	this->setSize(sf::Vector2f(m_text.getGlobalBounds().width+10, m_text.getGlobalBounds().height+10));
	this->centerText();
}

void BoutonTexte::centerText(){
	m_text.setOrigin(m_text.getLocalBounds().width/2, m_text.getLocalBounds().height/2);
	m_text.setPosition(m_position.x + m_size.x/2, m_position.y + m_size.y/2 - 3*(m_text.getCharacterSize()/10));
}

void BoutonTexte::modifStyle(bool bold, bool italic, bool underlined, bool strikeThrough){
	m_style[0] = bold;
	m_style[1] = italic;
	m_style[2] = underlined;
	m_style[3] = strikeThrough;
}

void BoutonTexte::initStyle(){
	switch(m_text.getStyle()){
		case 0: // Default
			modifStyle(false, false, false, false); break;
		case 1: // Bold
			modifStyle(true, false, false, false); break;
		case 2: // Italic
			modifStyle(false, true, false, false); break;
		case 4: // Underlined
			modifStyle(false, false, true, false); break;
		case 8: // StrikeThrough
			modifStyle(false, false, false, true); break;
		case 3: // Bold + Italic
			modifStyle(true, true, false, false); break;
		case 5: // Bold + Underlined
			modifStyle(true, false, true, false); break;
		case 9: // Bold + StrikeThrough
			modifStyle(true, false, false, true); break;
		case 6: // Italic + Underlined
			modifStyle(false, true, true, false); break;
		case 10: // Italic + StrikeThrough
			modifStyle(false, true, false ,true); break;
		case 12: // Underlined + StrikeThrough
			modifStyle(false, false, true, true); break;
		case 7: // Bold + Italic + Underlined
			modifStyle(true, true, true, false); break;
		case 11: // Bold + Italic + StrikeThrough
			modifStyle(true, true, false, true); break;
		case 13: // Bold + Underlined + StrikeThrough
			modifStyle(true, false, true, true); break;
		case 14: // Italic + Underlined + StrikeThrough
			modifStyle(false, true, true, true); break;
		case 15: // Bold + Italic + Underlined + StrikeThrough
			modifStyle(true, true, true, true); break;
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////// Fonctions de la classe BoutonImage //////////////////////
////////////////////////////////////////////////////////////////////////////////