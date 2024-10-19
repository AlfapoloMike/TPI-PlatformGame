#pragma once
#include "Enemigo.h"

class Skull : public Enemigo{

private:

public:
	Skull(std::string texture, sf::Vector2f newPosition, sf::Vector2f newVelocity);
	void updateSkull();
	void move();

};
