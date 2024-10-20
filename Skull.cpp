#include "Skull.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Skull::Skull(sf::Vector2f newPosition, sf::Vector2f newVelocity) :Enemigo(newPosition, newVelocity)
{
	_animationState = AnimationState::IDLE_BASIC;
	setAnimationState();
	_sprite.setOrigin(_animation.getUvRect().width/2.0, _animation.getUvRect().height);
}

void Skull::updateSkull(int row, float deltaTime)
{
	
	animationControl();
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
		_animationState = HIT_WALL;
		setAnimationState();
	}
	if (_sprite.getGlobalBounds().getPosition().x <= (60)) {
		_velocity.x = _velocity.x * -1;
		_sprite.scale(-1, 1);
		_animationState = HIT_WALL;
		setAnimationState();

	}
	if (_sprite.getGlobalBounds().getPosition().y >= (540 - _animation.uvRect.height)) {
		
		_velocity.y = _velocity.y * -1;
		_animationState = HIT_WALL;
		setAnimationState();

	}
	
	if (_sprite.getGlobalBounds().getPosition().y <= (60)) {
		_velocity.y = _velocity.y * -1;
		_animationState = HIT_WALL;
		setAnimationState();

	}
	
		_sprite.move(_velocity.x, _velocity.y);
}

void Skull::SetTextureRectAnimated() {
	
	_sprite.setTextureRect(_animation.uvRect);

}

void Skull::setAnimationState()
{
	if (_animationState == IDLE_BASIC) {
		setTexture("./assets/enemigos/Skull/Idle_Basic(52x54).png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_animationState == HIT_WALL) {

		setTexture("./assets/enemigos/Skull/Hit_Wall_2_(52x54).png");
		_animation.setImageCount(sf::Vector2u(7, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);

	}

}

void Skull::animationControl()
{
	if (_animationState == HIT_WALL) {
		_animationTimeCounter += 0.09f;
		if (_animationTimeCounter >= 2.43) {
			_animationState = IDLE_BASIC;
			setAnimationState();
			_animationTimeCounter = 0;
		}
	}
}

Skull::~Skull()
{
}

