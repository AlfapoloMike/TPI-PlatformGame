#include "IceBall.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

IceBall::IceBall(sf::Vector2f newPosition, int pixelMetro, b2World& world)
{
	setAnimationState();
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	_sprite.setPosition(newPosition.x * pixelMetro, 600 - newPosition.y * pixelMetro);
	_sprite.setScale(1, 1);
	//_sprite.setScale(0.6, 0.6);
	setPositionBody(newPosition);
	setBodyInWorld(world);
	setSizeBody();
	setFixture();
}


//***************BOX2D****************************/
void IceBall::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DEL CUERPO
	///_bodyDef.position.Set(newPosition.x, newPosition.y);
	_bodyDef.position.Set(newPosition.x, newPosition.y);

	_bodyDef.type = b2_dynamicBody;

}

void IceBall::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);

	/////////asgina a travez de un puntero el objeto conejo al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	////// Asignamos una escala de gravedad 0 para que no sea afectado por la gravedad.
	_body->SetGravityScale(0.0f);
	setRandomDirection();
	_body->SetLinearVelocity(b2Vec2(_velocidad.x, _velocidad.y));
}

void IceBall::setSizeBody()
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(0.6f, 0.6f);
}

void IceBall::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 1.0f;   // DENSISDAD
	_fixtureDef.friction = 0.5f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = ICEBALL;
	_fixtureDef.filter.maskBits = PLAYER | WALL;

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 IceBall::getPositionBody()
{
	b2Vec2 position = _body->GetPosition();
	return position;
}
//***************BOX2D****************************/

///corregir nombre a destroyBody
void IceBall::checkBody(b2World& world) {


	if (_state == ICEBALL_STATE::DESACTIVADO && destroyed == false) {

		if (_body != nullptr) {
		world.DestroyBody(_body);
		destroyed = true;
		}

	}
}

void IceBall::AnimationControl(float deltaTime) {

	if (_state == ICEBALL_STATE::ACTIVADO) {
		timer += deltaTime;
		if (timer > 0.4f) {
			_state = ICEBALL_STATE::DESACTIVADO;
			timer = 0;
			setAnimationState();
		}
	}
}

void IceBall::setRandomDirection() {

	int random = rand() % 4 + 1;

	if (random == 1) {
		_velocidad.x = -1*_velocidad.x;
		_velocidad.y = _velocidad.y;
	}
	else if (random == 2) {
		_velocidad.x = -1*_velocidad.x;
		_velocidad.y = -1*_velocidad.y;
	}
	else if (random == 3) {
		_velocidad.x = _velocidad.x;
		_velocidad.y = _velocidad.y;
	}
	else if (random == 4) {
		_velocidad.x = _velocidad.x;
		_velocidad.y = -1*_velocidad.y;
	}


}

void IceBall::setNewDirection(bool horizontalSide, bool verticalSide) {

	if (horizontalSide == true) {
		_velocidad.x = -1 * _velocidad.x;
		_velocidad.y = _velocidad.y;
	}
	else if(verticalSide == true){
		_velocidad.x =  _velocidad.x;
		_velocidad.y = -1 * _velocidad.y;
	}
	
	_body->SetLinearVelocity(b2Vec2(_velocidad.x, _velocidad.y));

}

void IceBall::move() {


	_body->SetLinearVelocity(b2Vec2(_velocidad.x, _velocidad.y));

}

void IceBall::setSpritePosition(sf::Vector2f newPosition) {
	_sprite.setPosition(newPosition.x, newPosition.y);
}

void IceBall::setTexture(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void IceBall::SetTextureRectAnimated() {

	_sprite.setTextureRect(_animation.uvRect);

}

void IceBall::setAnimationState()
{
	if (_state == ICEBALL_STATE::FLOATING) {
		setTexture("./assets/mago/spells/iceBall.png");
		_animation.setImageCount(sf::Vector2u(4, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == ICEBALL_STATE::ACTIVADO) {
		setTexture("./assets/mago/spells/iceExplotion.png");
		_animation.setImageCount(sf::Vector2u(7, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == ICEBALL_STATE::DESACTIVADO) {
		setTexture("./assets/mago/spells/laserdesactivado.png");
		_animation.setImageCount(sf::Vector2u(7, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}


}


void IceBall::Update(int row, float deltaTime, sf::Vector2f newPosition, b2World& world) {

	if (_state == ICEBALL_STATE::FLOATING) {
		_positionBody = _body->GetPosition();
		move();
	}
	AnimationControl(deltaTime);
	_sprite.setPosition(_positionBody.x * 40, 600 - (_positionBody.y * 40));
	_sprite.setTextureRect(_animation.uvRect);
	_animation.Update(row, deltaTime);
	checkBody(world);

}



void IceBall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}
void IceBall::explodeBall() {

	_state = ICEBALL_STATE::ACTIVADO;
	setAnimationState();
}

bool IceBall::Destroyed() {

	return destroyed;
}

sf::Sprite IceBall::getShape() {
	return _sprite;
}