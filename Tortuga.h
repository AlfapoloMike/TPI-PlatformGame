#pragma once
#include "Aldeano.h"

class Tortuga : public Aldeano {

public:
	Tortuga(sf::Vector2f newPosition, sf::Vector2f newVelocity);
	void update(int row, float deltaTime);
	//void move(); Tortuga no se mueve
	void SetTextureRectAnimated();
	void setAnimationState();
	void animationControl();
	~Tortuga();

private:
	enum AnimationState {
		ESPINAS_EXT,
		ESPINAS_RET,
		ESPINAS_IDLE,
		IDLE
	};

	AnimationState _animationState;
	float _animationTimeCounter = 0;
	bool _espinas;
};

