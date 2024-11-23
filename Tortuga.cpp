#include "Tortuga.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Tortuga::Tortuga(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float pixelMetro) :Aldeano(newPosition, newVelocity, pixelMetro) {

	_animationState = AnimationState::IDLE;

	setPositionBody(newPosition);
	setBodyInWorld(world);
	setSizeBody(newSize);
	setFixture();
	_velocidad = 0.01f;
	setAnimationState();
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	setPosition(sf::Vector2f(newPosition.x, newPosition.y), pixelMetro);
	_sprite.setScale(-1, 1);
	_size = newSize;
	//_espinas = false;


}

void Tortuga::updateVillager(int row, float deltaTime)
{
	move(2.0f);
	animationControl(deltaTime);
	_sprite.setPosition(_positionBody.x * 40, 600 - _positionBody.y * 40);
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.getUvRect().width / 2.f, _animation.getUvRect().height / 2.f);
	_animation.Update(row, deltaTime);

}


void Tortuga::setNewDirection(bool lado)
{

	if (lado == true) {
		if (_velocidad < 0) {
			_velocidad = _velocidad * -1;
			_sprite.setScale(-1, 1);
		}


	}
	else if (lado == false) {
		if (_velocidad > 0) {
			_velocidad = _velocidad * -1;
			_sprite.setScale(1, 1);
		}
	}
}

void Tortuga::setContact(bool state)
{
	_contacting = state;
}

void Tortuga::setBorderWalk(float izquierdo, float derecho)
{
	_limiteIzq = izquierdo;
	_limiteDer = derecho;
	_velocidad = 2.0f;
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
		_animation.setSwitchTime(0.12f);
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
		_animation.setSwitchTime(0.12f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_animationState == AnimationState::HITTED) {
		setTexture("./assets/aldeanos/Turtle/Hit(44x26).png");
		_animation.setImageCount(sf::Vector2u(5, 1));
		_animation.setSwitchTime(0.12f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_animationState == AnimationState::IDLE && _alive == false) {
		setTexture("./assets/aldeanos/Turtle/Idle1_free(44x26).png");
		_animation.setImageCount(sf::Vector2u(14, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
}

void Tortuga::animationControl(float deltaTime) {  /// Control de tiempo por animacion

	if (_animationState == IDLE) {
		
		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 3.78f) { // 2.43segs Termina IDLE y extiende espinas
			if (_alive == true) {
			_animationState = ESPINAS_EXT;
			_spikes = true;
			_animationTimeCounter = 0;
			setAnimationState();
			}
		}
		
	}

	if (_animationState == ESPINAS_EXT) {
		
		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 0.9f) { // 0.37segs Termin0 de extenderlas y comienzan permanencer activas
			_animationState = ESPINAS_IDLE;
			_animationTimeCounter = 0;
			setAnimationState();

		}
		
	}
	if (_animationState == ESPINAS_IDLE) {
		
		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 3.78f) { // 2.43segs Terminan las espinas activas y comienza a retraerlas.
			_animationState = ESPINAS_RET;
			_animationTimeCounter = 0;
			setAnimationState();

		}
		
	}
	if (_animationState == ESPINAS_RET) {
		
		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 0.9f) { //0.37segs Termina de retraerlas y vuelve a estado inicial IDLE.
			_spikes = false;
			_animationState = IDLE;
			setAnimationState();
			_animationTimeCounter = 0;
		}
		
	}
	if (_animationState == HITTED) {
		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 0.4f) { //0.37segs Termina de retraerlas y vuelve a estado inicial IDLE.
			_spikes = false;
			_animationState = IDLE;
			setAnimationState();
			_animationTimeCounter = 0;
		}
	}
}

Tortuga::~Tortuga(){
}

void Tortuga::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DEL CUERPO
	_bodyDef.bullet = true;
	_bodyDef.position.Set(newPosition.x, newPosition.y);
	_bodyDef.type = b2_dynamicBody;
}

void Tortuga::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);


	/////////asgina a travez de un puntero el objeto al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Tortuga::setSizeBody(sf::Vector2f newSize)
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(newSize.x, newSize.y);
}

void Tortuga::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 1.0f;   // DENSISDAD
	_fixtureDef.friction = 0.3f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = TURTLE;
	_fixtureDef.filter.maskBits = WALL | PLAYER | PLATFORM;

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 Tortuga::getPositionBody()
{
	b2Vec2 position = _body->GetPosition();
	return position;
}

bool Tortuga::getSpikes()
{
	return _spikes;
}

void Tortuga::move(float velocidad)
{
	_positionBody = getPositionBody();


	// CAMBIA DE DIRECCION
	if (_positionBody.x <= _limiteIzq + _size.x ) {
		_velocidad = 2; // Invertir la velocidad
		_sprite.setScale(-1, 1);
		_contacting = false;
	}
	else if (_positionBody.x >= _limiteDer - _size.x) {
		_velocidad = -2; // Invertir la velocidad
		_sprite.setScale(1, 1);
		_contacting = false;
	}


	///// SE GUARDA LA VELOCIDAD ACTUAL DE X E Y
	b2Vec2 velocidadActual = _body->GetLinearVelocity();
	///// SE PASA LA VELOCIDAD DE Y ACTUAL, Y LA NUEVA VELOCIDAD DE X (_velocidad esta seteado como propiedad de clase)
	_body->SetLinearVelocity(b2Vec2(_velocidad, velocidadActual.y));
}

void Tortuga::recibeDanio() {
	

	_alive = false;
	b2Filter filtro = _body->GetFixtureList()->GetFilterData();
	filtro.maskBits &= ~PLAYER;
	_body->GetFixtureList()->SetFilterData(filtro);
	_animationState = HITTED;
	setAnimationState();
	_animationTimeCounter = 0;
}