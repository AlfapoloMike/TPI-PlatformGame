#pragma once
#include "Enemigo.h"

class Skull : public Enemigo{

private:

public:
	Skull(std::string texture, sf::Vector2f newPosition, sf::Vector2f newVelocity, sf::Vector2u(spriteMatriz), float timeByFPS);
	void updateSkull(int row, float deltaTime);
	void move();

	void SetTextureRectAnimated();

};
