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
	Skull(sf::Vector2f newPosition, sf::Vector2f newVelocity, float pixelMetro);
	void move();
	void SetTextureRectAnimated();
	void setAnimationState();
	void animationControl();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateEnemie(int row, float deltaTime) override;

	sf::Sprite getSpriteSkull();
	Skull();
	~Skull();
};


