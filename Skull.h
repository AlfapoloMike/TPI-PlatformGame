#pragma once
#include "Enemigo.h"

enum AnimationState {
	IDLE_BASIC, HIT_WALL
};

class Skull : public Enemigo{

private:
	AnimationState _animationState;
	float _animationTimeCounter = 0;
public:
	Skull(std::string texture, sf::Vector2f newPosition, sf::Vector2f newVelocity, sf::Vector2u(spriteMatriz), float timeByFPS);
	void updateSkull(int row, float deltaTime);
	void move();
	void SetTextureRectAnimated();
	void setAnimationState();
	void animationControl();
	~Skull();
};


