#include "Corazon.h"

Corazon::Corazon(sf::Vector2f newPosition)
{
	_sprite.setPosition(sf::Vector2f(newPosition.x,newPosition.y));
	_state = STATES_HEART::IDLE;
	setTextura();
	setAnimation();
	_sprite.setScale(1.3, 1.3);
}

Corazon::Corazon()
{
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
		_animation.setSwitchTime(0.12f);
	}
	if (_state == STATES_HEART::RESTORED) {
		_animation.setSwitchTime(0.09f);
	}

}

void Corazon::controlAnimation(float deltaTime)
{
	///////////////////// RANDOM PARA TESTEAR COMO SI EL PERSONAJE SUFRIERA DAÑOS

		_active = true;


	////// CONTROLO EL TIEMPO DE CADA ANIMACION Y SU SECUENCIA
	///// SI ES TRUE = EL CORAZON ESTA ACTIVO Y LAS ANIMACIONES SON DEL CORAZON LLENO
	///// SI ES FALSE = EL CORAZON SE DAÑO Y SE HACE UNA SECUENCIA DEL CORAZON ROMPIENDOSE

	if (_state == STATES_HEART::IDLE && _active == true) {

		if (_animationCounterTime >= 14.0f) {


				_state = STATES_HEART::SHINE;
				setAnimation();
				_animationCounterTime = 0;
				_filaAnimation = 1;
				_columnAnimation = 10;


		}

		_animationCounterTime += 0.09f;

	}else if (_state == STATES_HEART::SHINE && _active == true) {
		_animationCounterTime += 0.09f;
		if (_animationCounterTime >= 1.54f) {
			_state = STATES_HEART::IDLE;
			setAnimation();
			_animationCounterTime = 0;
			_filaAnimation = 0;
			_columnAnimation = 10;

		}
	}
	if (_active == false) {
		
		if (_state != STATES_HEART::HITTED && _state != STATES_HEART::DAMAGED) {
			_state = STATES_HEART::HITTED;
			setAnimation();
			_animationCounterTime = 0;
			_filaAnimation = 2;
			_columnAnimation = 6;

		}
		else if (_state == STATES_HEART::HITTED) {
			_animationCounterTime += 0.09f;
			if (_animationCounterTime >= 3.4f) {
				_state = STATES_HEART::DAMAGED;
				setAnimation();
				_animationCounterTime = 0;
				_filaAnimation = 6;
				_columnAnimation = 0;
			}
		}
	}


	////// CONTROLO LA ANIMACION CON SOBRE CARGA
	///// SI NECESITO LIMITAR LA X PORQUE LA ANIMACION NO OCUPA 10 COLUMNAS, USO SOBRECARGA
	///// SI EL VALOR DE COLUMNAS ES 10, USO LA ANIMACION CLASICA
	if (_columnAnimation == 10) {
		_animation.Update(_filaAnimation, deltaTime);
	}
	else {
		_animation.Update(_filaAnimation, deltaTime, _columnAnimation);

	}

}

void Corazon::update(float deltaTime)
{
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.getUvRect().width / 2.0, _animation.getUvRect().height / 2.0);
	controlAnimation(deltaTime);

}

sf::Sprite Corazon::getSprite()
{
	return _sprite;
}

void Corazon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}

Corazon::~Corazon()
{
}
