#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

enum STATES_HEART {
	IDLE, RESTORED, HITTED, DAMAGED, SHINE
};

class Corazon: public sf::Drawable{

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	Animation _animation;
	STATES_HEART _state = STATES_HEART::IDLE;
	bool _active = true;
	int _filaAnimation = 0;
	int _columnAnimation = 10;
	float _animationCounterTime = 0;

public:
	Corazon(sf::Vector2f newPosition);
	Corazon();
	void setPosition(sf::Vector2f newPosition);
	void setTextura();
	void SetTextureRectAnimated();
	void setAnimation();
	void controlAnimation(float deltaTime);
	void setActive(bool newState);
	void update(float deltaTime);
	sf::Sprite getSprite();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~Corazon();

};