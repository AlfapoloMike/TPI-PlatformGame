#include "Skull.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Skull::Skull(std::string texture, sf::Vector2f newPosition, sf::Vector2f newVelocity, sf::Vector2u(spriteMatriz), float timeByFPS) :Enemigo(texture, newPosition, newVelocity)
{
	Animation animacionAux(&_texture, sf::Vector2u(spriteMatriz), timeByFPS); ///// CREO UNA VARIABLE DE ANIMACION (ESPECIFICA)
	_animation = animacionAux;

	_sprite.setOrigin(_animation.getUvRect().width/2.0, _animation.getUvRect().height);

}

void Skull::updateSkull(int row, float deltaTime)
{
	
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.getUvRect().width / 2.0, _animation.getUvRect().height / 2.0);
	_animation.Update(row, deltaTime);
	move();
}

void Skull::move()
{
	
	if (_sprite.getGlobalBounds().getPosition().x >= (740 - _animation.uvRect.width)) {
		_velocity.x = _velocity.x * -1;
		_sprite.scale(-1, 1);

	}
	if (_sprite.getGlobalBounds().getPosition().x <= (60)) {
		_velocity.x = _velocity.x * -1;
		_sprite.scale(-1, 1);
	}
	if (_sprite.getGlobalBounds().getPosition().y >= (540 - _animation.uvRect.height)) {
		
		_velocity.y = _velocity.y * -1;
	}
	
	if (_sprite.getGlobalBounds().getPosition().y <= (60)) {
		_velocity.y = _velocity.y * -1;
	}
	
		_sprite.move(_velocity.x, _velocity.y);
}

void Skull::SetTextureRectAnimated() {
	
	_sprite.setTextureRect(_animation.uvRect);

}