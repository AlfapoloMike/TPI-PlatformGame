#include "Aldeano.h"


Aldeano::Aldeano(sf::Vector2f newPosition, sf::Vector2f newVelocity){
	setPosition(newPosition);
	setVelocity(newVelocity);
}

/// SETTERS
void Aldeano::setTexture(std::string texture){
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Aldeano::setPosition(sf::Vector2f newPosition){
	_sprite.setPosition(sf::Vector2f(newPosition.x, newPosition.y));
}

void Aldeano::setSprite(){
}

void Aldeano::setVelocity(sf::Vector2f newVelocity){
	_velocity.x = newVelocity.x;
	_velocity.y = newVelocity.y;
}

/// GETTERS
sf::Sprite Aldeano::getSprite(){
	return _sprite;
}

sf::Texture Aldeano::getTexture(){
	return _texture;
}

sf::Vector2f Aldeano::getPosition(){
	return _position;
}

sf::Vector2f Aldeano::getVelocity(){
	return _velocity;
}


void Aldeano::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(_sprite, states);

}

sf::FloatRect Aldeano::getBounds() const {
	return _sprite.getGlobalBounds();
}

Aldeano::~Aldeano(){
}
