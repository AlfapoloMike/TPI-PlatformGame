#include "Personaje.h"
#include <iostream>



Personaje::Personaje()
{
	sf::Vector2f spriteSize;
	_texture.loadFromFile("Fall_(32x32).png");
	spriteSize.x = _sprite.getGlobalBounds().getSize().x;
	spriteSize.y = _sprite.getGlobalBounds().getSize().y;
	_sprite.setTexture(_texture);
	_sprite.setPosition(sf::Vector2f(150.0f, 150.0f));
	_estado = ESTADOS_JUGADOR::QUIETO;
}

void Personaje::personajeUpdate()
{

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	//	_sprite.move(0, -_velocity);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		//_sprite.move(0, +_velocity);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_sprite.move(-_velocity.x, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_sprite.move(+_velocity.x, 0);
	}

	///// VALIDACION TERRENO PROVISIONAL
	sf::Vector2f spriteGlobalSize;

	spriteGlobalSize.x = _sprite.getGlobalBounds().getSize().x;
	spriteGlobalSize.y = _sprite.getGlobalBounds().getSize().y;
	if (_sprite.getGlobalBounds().getPosition().x > (740 - spriteGlobalSize.x)) {
		_sprite.setPosition(740 - spriteGlobalSize.x, _sprite.getGlobalBounds().getPosition().y);
	}
	if (_sprite.getGlobalBounds().getPosition().x < (60)) {
		_sprite.setPosition(60, _sprite.getGlobalBounds().getPosition().y);
	}
	if (_sprite.getGlobalBounds().getPosition().y > (480 - spriteGlobalSize.y)) {
		_sprite.setPosition(_sprite.getGlobalBounds().getPosition().x, 480 - spriteGlobalSize.y);
	}
	if (_sprite.getGlobalBounds().getPosition().y < (60)) {
		_sprite.setPosition(_sprite.getGlobalBounds().getPosition().x, 60);
	}


	

}

sf::Sprite Personaje::getDraw()
{
	return _sprite;
}


void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}

void Personaje::setPosition(sf::Vector2f NewPosition)
{
}

Personaje::~Personaje()
{
}
