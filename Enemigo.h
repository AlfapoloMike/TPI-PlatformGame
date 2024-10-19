#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"

class Enemigo : public sf::Drawable{
protected:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	Animation _animation;
public:
	Enemigo(std::string texture, sf::Vector2f newPosition, sf::Vector2f newVelocity);
	void setTexture(std::string texture);
	void setPosition(sf::Vector2f newPosition);
	void setSprite();
	void setVelocity(sf::Vector2f newVelocity);
	sf::Sprite getSprite();
	sf::Texture getTexture();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};