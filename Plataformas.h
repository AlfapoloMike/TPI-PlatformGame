#pragma once
#include "SFML/Graphics.hpp"

class Plataformas : public sf::Drawable {
private:
	sf::RectangleShape _shape;
	
public:
	Plataformas(sf::Vector2f newPosition, sf::Vector2f newSize);
	void setPositionPlataforma(sf::Vector2f newPosition);
	void setSizePlataforma(sf::Vector2f newSize);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~Plataformas();

};