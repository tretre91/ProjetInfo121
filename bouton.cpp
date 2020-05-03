#include "bouton.hpp"
using namespace std;

string wdir(){
	string s = __FILE__;
	for(int i = s.size()-1; i >= 0; i--)
		if(s[i] == '/'){
			s.erase(i+1, s.size());
			break;
		}
	return s;
}

/* Constructeurs de la classe Bouton */

Bouton::Bouton() : m_size(40.f, 20.f), m_position(0.f, 0.f),m_color(sf::Color(140, 140, 140)){
	m_base.setSize(m_size);
	m_base.setPosition(m_position);
	m_base.setFillColor(m_color);
	m_base.setOutlineThickness(-2);
	m_base.setOutlineColor(m_color + sf::Color(30,30,30));
	
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text("Bouton", m_font, 10);
	this->centerText();
}

Bouton::Bouton(sf::Vector2f const& size) : m_size(size), m_position(0.f, 0.f),m_color(sf::Color(140, 140, 140)){
	m_base.setSize(m_size);
	m_base.setPosition(m_position);
	m_base.setFillColor(m_color);
	m_base.setOutlineThickness(-2);
	m_base.setOutlineColor(m_color + sf::Color(30,30,30));
	
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text("Bouton", m_font, 10);
	this->centerText();
}

Bouton::Bouton(sf::Vector2f const& size, sf::Color const& color) : m_size(size), m_position(0.f, 0.f),m_color(color){
	m_base.setSize(m_size);
	m_base.setPosition(m_position);
	m_base.setFillColor(m_color);
	m_base.setOutlineThickness(-2);
	m_base.setOutlineColor(m_color + sf::Color(30,30,30));
	
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text("Bouton", m_font, 10);
	this->centerText();
}

Bouton::Bouton(sf::Vector2f const& position, sf::Vector2f const& size) : m_size(size), m_position(position),m_color(sf::Color(140, 140, 140)){
	m_base.setSize(m_size);
	m_base.setPosition(m_position);
	m_base.setFillColor(m_color);
	m_base.setOutlineThickness(-2);
	m_base.setOutlineColor(m_color + sf::Color(30,30,30));
	
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text("Bouton", m_font, 10);
	this->centerText();
}

Bouton::Bouton(sf::Vector2f const& position, sf::Vector2f const& size, sf::Color const& color) : m_size(size), m_position(position),m_color(color){
	m_base.setSize(m_size);
	m_base.setPosition(m_position);
	m_base.setFillColor(m_color);
	m_base.setOutlineThickness(-2);
	m_base.setOutlineColor(m_color + sf::Color(30,30,30));
	
	if(!m_font.loadFromFile(wdir()+"Ressources/arial.ttf")){
		cout << "Erreur lors du chargement de la police" << endl;
	}
	m_text = sf::Text("Bouton", m_font, 10);
	this->centerText();
}

/* Modification de la couleur du bouton */

void Bouton::setColor(sf::Color const& color){
	m_color = color;
	m_base.setFillColor(color);
	m_base.setOutlineColor(color + sf::Color(30,30,30));
}

void Bouton::setColor(int const& r, int const& g, int const& b, int alpha = 255){
	m_color = sf::Color(r, g, b, alpha);
	m_base.setFillColor(m_color);
	m_base.setOutlineColor(m_color + sf::Color(30,30,30));
}

sf::Color Bouton::getColor() const{
	return m_color;
}

/* Modification de la position du bouton */

void Bouton::setPosition(int const& x, int const& y){
	m_position = sf::Vector2f(x, y);
	m_base.setPosition(m_position);
	this->centerText();
}

void Bouton::setPosition(sf::Vector2f const& pos){
	m_position = pos;
	m_base.setPosition(m_position);
	this->centerText();
}

sf::Vector2f Bouton::getPosition() const{
	return m_position;
}

/* Modification de la taille du bouton */

void Bouton::setSize(int const& largeur, int const& hauteur){
	m_size = sf::Vector2f(largeur, hauteur);
	m_base.setSize(m_size);
	this->centerText();
}

void Bouton::setSize(sf::Vector2f const& taille){
	m_size = taille;
	m_base.setSize(m_size);
	this->centerText();
}

sf::Vector2f Bouton::getSize() const{
	return m_size;
}

/* Modification du texte du bouton */

void Bouton::setText(string const& texte){
	m_text.setString(texte);
	this->centerText();
}

void Bouton::setText(sf::Text const& texte){
	m_text = texte;
	this->centerText();
}

sf::Text Bouton::getText() const{
	return m_text;
}

std::string Bouton::getString() const{
	return m_text.getString();
}

void Bouton::setTextSize(uint taille){
	m_text.setCharacterSize(taille);
	this->centerText();
}

/* Tests en rapport avec la position du bouton */

bool Bouton::contient(int const& x, int const& y) const{
	return x >= m_position.x && x <= m_position.x + m_size.x && y >= m_position.y && y <= m_position.y + m_size.y;
}
bool Bouton::contient(sf::Vector2f const& coord) const{
	return coord.x >= m_position.x && coord.x <= m_position.x + m_size.x && coord.y >= m_position.y && coord.y <= m_position.y + m_size.y;
}

/* Dessin du bouton */

void Bouton::dessiner(sf::RenderWindow &window){
	window.draw(m_base);
	window.draw(m_text);
}

/* Méthodes protégées */

void Bouton::centerText(){
	m_text.setOrigin(m_text.getLocalBounds().width/2, m_text.getLocalBounds().height/2);
	m_text.setPosition(m_position.x + m_size.x/2, m_position.y + m_size.y/2 - 3*(m_text.getCharacterSize()/10));
}