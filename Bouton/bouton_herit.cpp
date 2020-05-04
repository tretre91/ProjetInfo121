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
	this->adaptText();
}

BoutonTexte::BoutonTexte(sf::Vector2f const& size) : Bouton(size){
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text("Bouton", m_font, 20);
	this->adaptText();
}

BoutonTexte::BoutonTexte(std::string const& texte) : Bouton(){
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text(texte, m_font, 20);
	if(fitText())
		this->centerText();
	else
		this->adaptText();
}

BoutonTexte::BoutonTexte(sf::Text const& texte) : Bouton(){
	m_text = texte;
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
	this->adaptText();
}

BoutonTexte::BoutonTexte(sf::Vector2f const& position, sf::Text const& texte) : Bouton(position, sf::Vector2f(5,5)){
	m_text = texte;
	this->adaptText();
}

BoutonTexte::BoutonTexte(sf::Vector2f const& position, sf::Vector2f const& size, std::string const& texte) : Bouton(position, size){
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text(texte, m_font, 20);
	this->adaptText();
}
	
BoutonTexte::BoutonTexte(sf::Vector2f const& position, sf::Vector2f const& size, sf::Text const& texte) : Bouton(position, size){
	m_text = texte;
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

void BoutonTexte::setUnderline(bool underline){
	m_text.setStyle(sf::Text::Underlined);
	this->adaptText();
}

void BoutonTexte::setBold(bool bold){
	m_text.setStyle(sf::Text::Bold);
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
	cout << m_text.getStyle() << endl;
	this->centerText();
}

void BoutonTexte::centerText(){
	m_text.setOrigin(m_text.getLocalBounds().width/2, m_text.getLocalBounds().height/2);
	m_text.setPosition(m_position.x + m_size.x/2, m_position.y + m_size.y/2 - 3*(m_text.getCharacterSize()/10));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////// Fonctions de la classe BoutonImage //////////////////////
////////////////////////////////////////////////////////////////////////////////