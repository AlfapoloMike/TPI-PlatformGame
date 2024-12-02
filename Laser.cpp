#include "Laser.h"
#include <iostream>


Laser::Laser(sf::Vector2f newPosition, int pixelMetro, bool sideR)
{
	_sideR = sideR;
	setAnimationState();
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	_sprite.setPosition(newPosition.x*pixelMetro , 600 - newPosition.y*pixelMetro);
	if (_sideR == true) {
		_sprite.setScale(-5.5, 1.2);

	}
	else {
		_sprite.setScale(5.5, 1.2);

	}
}


//***************BOX2D****************************/
void Laser::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DEL CUERPO
	///_bodyDef.position.Set(newPosition.x, newPosition.y);
	_bodyDef.position.Set(newPosition.x, newPosition.y);

	_bodyDef.type = b2_dynamicBody;

}

void Laser::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);

	/////////asgina a travez de un puntero el objeto conejo al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	////// Asignamos una escala de gravedad 0 para que no sea afectado por la gravedad.
	_body->SetGravityScale(0.0f);
	_body->SetLinearVelocity(b2Vec2(_velocidad.x, _velocidad.y));
}

void Laser::setSizeBody()
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	if (_sideR) {
		_bodyBox.SetAsBox(33.0f, 0.1f);
	}
	else {
		_bodyBox.SetAsBox(36.5f, 0.1f);

	}
}

void Laser::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 1.0f;   // DENSISDAD
	_fixtureDef.friction = 0.5f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = LASER;
	_fixtureDef.filter.maskBits = PLAYER;

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 Laser::getPositionBody()
{
	b2Vec2 position = _body->GetPosition();
	return position;
}
//***************BOX2D****************************/

void Laser::createOrDestroyBody(sf::Vector2f newPosition,b2World& world) {

	if (_state == LASER_STATE::ACTIVADO) {
		setPositionBody(newPosition);
		setBodyInWorld(world);
		setSizeBody();
		setFixture();
	}
	else if (_state == LASER_STATE::DESACTIVADO) {

		world.DestroyBody(_body);

	}
}

bool Laser::getSideR() {
	return _sideR;
}

void Laser::setSpritePosition(sf::Vector2f newPosition) {
	_sprite.setPosition(newPosition.x, newPosition.y);
}

void Laser::setTexture(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Laser::SetTextureRectAnimated() {

	_sprite.setTextureRect(_animation.uvRect);

}

void Laser::setAnimationState()
{
	if (_state == LASER_STATE::ACTIVADO) {
		setTexture("./assets/mago/spells/laser.png");
		_animation.setImageCount(sf::Vector2u(6, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == LASER_STATE::CARGANDO) {
		setTexture("./assets/mago/spells/lasercharging.png");
		_animation.setImageCount(sf::Vector2u(11, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}else if (_state == LASER_STATE::DESACTIVADO) {
		setTexture("./assets/mago/spells/laserdesactivado.png");
		_animation.setImageCount(sf::Vector2u(11, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}


}

void Laser::AnimationControl(float deltaTime, sf::Vector2f newPosition, b2World& world) {

	if (_state == LASER_STATE::ACTIVADO) {
		timer += deltaTime;
		if (timer >= 1.4f) {
			timer = 0;
			_state = LASER_STATE::DESACTIVADO;
			createOrDestroyBody(newPosition, world);
			setAnimationState();
		}
	}
	else if (_state == LASER_STATE::CARGANDO) {
		timer += deltaTime;
		if (timer >= 1.4f) {
			timer = 0;
			_state = LASER_STATE::ACTIVADO;
			setAnimationState();
			createOrDestroyBody(newPosition, world);
		}
	}
	else if (_state == LASER_STATE::DESACTIVADO) {
		timer += deltaTime;
		if (timer >= 1.4f) {
			timer = 0;
			_state = LASER_STATE::CARGANDO;
			setAnimationState();

		}
	}
}

void Laser::Update(int row, float deltaTime, sf::Vector2f newPosition, b2World& world) {
	
	AnimationControl(deltaTime, newPosition, world);
	if (_state == LASER_STATE::ACTIVADO) {
		_body->SetTransform(b2Vec2(newPosition.x, newPosition.y), 0.0f);
	}
	_sprite.setPosition(newPosition.x * 40, 600 - (newPosition.y * 40));
	_sprite.setTextureRect(_animation.uvRect);
	_animation.Update(row, deltaTime);

}



void Laser::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}

sf::Sprite Laser::getShape() {
	return _sprite;
}