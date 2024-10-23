#include "Tortuga.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Tortuga::Tortuga(sf::Vector2f newPosition, sf::Vector2f newVelocity) :Aldeano(newPosition, newVelocity) {

	_animationState = AnimationState::IDLE;
	_espinas = false;
	setAnimationState();
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height); /// Para evitar warning cast con float.
}

void Tortuga::update(int row, float deltaTime) {

	animationControl();
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.getUvRect().width / 2.f, _animation.getUvRect().height / 2.f);
	_animation.Update(row, deltaTime);
}

void Tortuga::SetTextureRectAnimated() {
	_sprite.setTextureRect(_animation.uvRect);

}

void Tortuga::setAnimationState() {


	if (_animationState == AnimationState::IDLE) {
		setTexture("./assets/aldeanos/Turtle/Idle2(44x26).png");
		_animation.setImageCount(sf::Vector2u(14, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_animationState == AnimationState::ESPINAS_EXT) {
		setTexture("./assets/aldeanos/Turtle/Spikesout(44x26).png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);

	}
	if (_animationState == AnimationState::ESPINAS_IDLE) {
		setTexture("./assets/aldeanos/Turtle/idle1(44x26).png");
		_animation.setImageCount(sf::Vector2u(14, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);

	}
	if (_animationState == AnimationState::ESPINAS_RET) {
		setTexture("./assets/aldeanos/Turtle/Spikesin(44x26).png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}

}

void Tortuga::animationControl() {  /// Control de tiempo por animacion

	if (_animationState == IDLE) {
		_animationTimeCounter += 0.01f;
		if (_animationTimeCounter >= 2.43) { // 2.43segs Termina IDLE y extiende espinas
			_animationState = ESPINAS_EXT;
			_animationTimeCounter = 0;
			setAnimationState();
		}
	}

	if (_animationState == ESPINAS_EXT) {
		_animationTimeCounter += 0.01f;
		if (_animationTimeCounter >= 0.37) { // 0.37segs Termin0 de extenderlas y comienzan permanencer activas
			_animationState = ESPINAS_IDLE;
			_espinas = true;
			_animationTimeCounter = 0;
			setAnimationState();

		}
	}
	if (_animationState == ESPINAS_IDLE) {
		_animationTimeCounter += 0.01f;
		if (_animationTimeCounter >= 2.43) { // 2.43segs Terminan las espinas activas y comienza a retraerlas.
			_animationState = ESPINAS_RET;
			_animationTimeCounter = 0;
			setAnimationState();

		}
	}
	if (_animationState == ESPINAS_RET) {
		_animationTimeCounter += 0.01f;
		if (_animationTimeCounter >= 0.37) { //0.37segs Termina de retraerlas y vuelve a estado inicial IDLE.
			_animationState = IDLE;
			_espinas = false;
			setAnimationState();
			_animationTimeCounter = 0;
		}
	}
}

Tortuga::~Tortuga(){
}

