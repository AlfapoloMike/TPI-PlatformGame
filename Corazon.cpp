#include "Corazon.h"

Corazon::Corazon(sf::Vector2f newPosition)
{
	_sprite.setPosition(sf::Vector2f(newPosition.x,newPosition.y));
	_state = STATES_HEART::IDLE;
	setTextura();
	setAnimation();
}


void Corazon::setTextura()
{
	_texture.loadFromFile("./assets/interfaz/hearts.png");
	_sprite.setTexture(_texture);
}

void Corazon::SetTextureRectAnimated()
{
	_sprite.setTextureRect(_animation.uvRect);

}

void Corazon::setAnimation()
{
	_animation.setImageCount(sf::Vector2u(10, 7));
	_animation.setImageUvRectSize(&_texture);

	if (_state == STATES_HEART::IDLE) {
		_animation.setSwitchTime(0.09f);
	}
	if (_state == STATES_HEART::SHINE) {
		_animation.setSwitchTime(0.09f);
	}
	if (_state == STATES_HEART::DAMAGED) {
		_animation.setSwitchTime(0.09f);
	}
	if (_state == STATES_HEART::HITTED) {
		_animation.setSwitchTime(0.09f);
	}
	if (_state == STATES_HEART::RESTORED) {
		_animation.setSwitchTime(0.09f);
	}

}

void Corazon::controlAnimation(float deltaTime)
{


	if (_state == STATES_HEART::IDLE && _active == true) {

		if (_animationCounterTime >= 3.6f) {

			int random = rand() % 1000 + 1;
			if (random > 998) {
				_state = STATES_HEART::SHINE;
				setAnimation();
				_animationCounterTime = 0;
				_filaAnimation = 1;
			}
		}

		_animationCounterTime += 0.09f;

	}else if (_state == STATES_HEART::SHINE && _active == true) {
		_animationCounterTime += 0.09f;
		if (_animationCounterTime >= 1.54f) {
			_state = STATES_HEART::IDLE;
			setAnimation();
			_animationCounterTime = 0;
			_filaAnimation = 0;
		}
	}
	if (_state == STATES_HEART::SHINE && _active == false) {

	}

	

}

void Corazon::update(float deltaTime)
{
	controlAnimation(deltaTime);
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.getUvRect().width / 2.0, _animation.getUvRect().height / 2.0);
	_animation.Update(_filaAnimation, deltaTime);

}

void Corazon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}

Corazon::~Corazon()
{
}
