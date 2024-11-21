#include "Enemigo.h"
#include <iostream>

Enemigo::Enemigo(sf::Vector2f newPosition, sf::Vector2f newVelocity, float pixelMetro)
{
	
	setPosition(newPosition, pixelMetro);
	setVelocity(newVelocity);

}

void Enemigo::setTexture(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Enemigo::setPosition(sf::Vector2f newPosition, float pixelMetro)
{
	_sprite.setPosition(sf::Vector2f(newPosition.x* pixelMetro, 600 - newPosition.y* pixelMetro));
}

void Enemigo::setSprite()
{
}

void Enemigo::setVelocity(sf::Vector2f newVelocity)
{
	_velocity.x = newVelocity.x;
	_velocity.y = newVelocity.y;
}

sf::Sprite Enemigo::getSprite()
{

	return _sprite;
}

sf::Texture Enemigo::getTexture()
{
	return _texture;
}


sf::Vector2f Enemigo::getPosition()
{
	return _position;
}

sf::Vector2f Enemigo::getVelocity()
{
	return _velocity;
}



void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}


Enemigo::Enemigo()
{
}

Enemigo::~Enemigo()
{
}
