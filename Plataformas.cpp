#include "Plataformas.h"


Plataformas::Plataformas(sf::Vector2f newPosition, sf::Vector2f newSize)
{
	setPositionPlataforma(newPosition);
	setSizePlataforma(newSize);
	_shape.setFillColor(sf::Color::Cyan);
}

void Plataformas::setPositionPlataforma(sf::Vector2f newPosition)
{
	_shape.setPosition(newPosition);
}

void Plataformas::setSizePlataforma(sf::Vector2f newSize)
{
	_shape.setSize(newSize);
}

void Plataformas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);

}

sf::FloatRect Plataformas::getBounds() const
{
	return _shape.getGlobalBounds();
}

Plataformas::~Plataformas()
{
}
