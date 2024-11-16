#include "Skull.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Skull::Skull(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float pixelMetro) :Enemigo(newPosition, newVelocity, pixelMetro)
{
	_animationState = AnimationState::IDLE_BASIC;
	setPositionBody(newPosition);
	setBodyInWorld(world);
	setSizeBody(newSize);
	setFixture();
	setAnimationState();
	//_sprite.setOrigin(newSize.x * 40, newSize.y * 40);
	_sprite.setOrigin((float)_animation.getUvRect().width/ 2, (float)_animation.getUvRect().height/2);
	setPosition(sf::Vector2f(newPosition.x * pixelMetro, 600 - newPosition.y * pixelMetro));
	_sprite.setScale(1, 1);
}

void Skull::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DEL CUERPO
	_bodyDef.position.Set(newPosition.x, newPosition.y);
	_bodyDef.type = b2_dynamicBody;

}

void Skull::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);

	/////////asgina a travez de un puntero el objeto conejo al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	////// Asignamos una escala de gravedad 0 para que no sea afectado por la gravedad.
	_body->SetGravityScale(0.0f);
	_body->SetLinearVelocity(b2Vec2(_velocidad.x, _velocidad.y));
}


void Skull::setSizeBody(sf::Vector2f newSize)
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(newSize.x, newSize.y);
}

void Skull::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 1.0f;   // DENSISDAD
	_fixtureDef.friction = 0.5f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = SKULLS;
	_fixtureDef.filter.maskBits = WALL | PLAYER;

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 Skull::getPositionBody()
{
	b2Vec2 position = _body->GetPosition();
	return position;
}

void Skull::setNewDirection(bool horizontalContact, bool verticalContact) {

	b2Vec2 velocidad = _body->GetLinearVelocity();


	if (horizontalContact == true) {

		_body->SetLinearVelocity(b2Vec2(velocidad.x*-1, velocidad.y));
		_sprite.scale(-1, 1);
		if (_animationState != HIT_WALL) {
			_animationState = HIT_WALL;
			setAnimationState();
		}

	}
	if (verticalContact == true) {
		_body->SetLinearVelocity(b2Vec2(velocidad.x, velocidad.y * -1));
		if (_animationState != HIT_WALL) {
			_animationState = HIT_WALL;
			setAnimationState();
		}
	}

}

void Skull::move()
{
	

	
	/*

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
	*/
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

void Skull::animationControl(float deltaTime)
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

void Skull::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}

void Skull::updateEnemie(int row, float deltaTime)
{

	b2Vec2 position = getPositionBody();


	move();
	animationControl(deltaTime);
	_sprite.setPosition(position.x * 40, 600 - position.y * 40);
	_sprite.setTextureRect(_animation.uvRect);
	_animation.Update(row, deltaTime);
}

sf::Sprite Skull::getSpriteSkull()
{
	return _sprite;
}

Skull::Skull()
{
		_animationState = AnimationState::IDLE_BASIC;
}

Skull::~Skull()
{
}



