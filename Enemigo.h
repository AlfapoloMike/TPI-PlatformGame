#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"

class Enemigo : public sf::Drawable{
protected:

	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::Vector2f _size;
	Animation _animation;
	///TEST DE TAMANIO
	//sf::RectangleShape _colisionSquare;

public:
	Enemigo(sf::Vector2f newPosition, sf::Vector2f newVelocity, float pixelMetro);

	// Setters
	void setTexture(std::string texture);
	void setPosition(sf::Vector2f newPosition, float pixelMetro);
	void setSprite();
	void setVelocity(sf::Vector2f newVelocity);

	// Getters
	sf::Sprite getSprite();
	sf::Texture getTexture();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();

	virtual void updateEnemie(int row, float deltaTime)=0;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Enemigo();
	~Enemigo();
};