#include "FatBird.h"




Fatbird::Fatbird(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float pixelMetro) :Aldeano(newPosition, newVelocity, pixelMetro) {

	_state = STATE::FALLING;

	setPositionBody(newPosition);
	setBodyInWorld(world);
	setSizeBody(newSize);
	setFixture();
	_velocidad = 0.01f;
	setAnimationState();
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	setPosition(sf::Vector2f(newPosition.x, newPosition.y), pixelMetro);
	_size = newSize;
	//_espinas = false;


}
//***************BOX2D****************************/

void Fatbird::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DEL CUERPO
	_bodyDef.position.Set(newPosition.x, newPosition.y);
	_bodyDef.type = b2_dynamicBody;
}

void Fatbird::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);

	/////////asgina a travez de un puntero el objeto al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Fatbird::setSizeBody(sf::Vector2f newSize)
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(newSize.x, newSize.y);
}

void Fatbird::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 1.0f;   // DENSISDAD
	_fixtureDef.friction = 0.3f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = FATBIRD;
	_fixtureDef.filter.maskBits = PLAYER | PLATFORM;

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 Fatbird::getPositionBody()
{
	b2Vec2 position = _body->GetPosition();
	return position;
}
//***************BOX2D****************************/


//***************SFML**************************/

void Fatbird::SetTextureRectAnimated() {
	_sprite.setTextureRect(_animation.uvRect);

}


void Fatbird::setAnimationState() {


	if (_state == STATE::IDLE) {
		setTexture("./assets/aldeanos/FatBird/Idle(40x48).png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}else if (_state == STATE::FALLING) {
		setTexture("./assets/aldeanos/fatbird/Fall(40x48).png");
		_animation.setImageCount(sf::Vector2u(4, 1));
		_animation.setSwitchTime(0.12f);
		_animation.setImageUvRectSize(&_texture);

	}else if (_state == STATE::HIT) {
		setTexture("./assets/aldeanos/fatbird/Hit(40x48).png");
		_animation.setImageCount(sf::Vector2u(5, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);

	}else if (_state == STATE::GROUND) {
		setTexture("./assets/aldeanos/fatbird/Ground(40x48).png");
		_animation.setImageCount(sf::Vector2u(4, 1));
		_animation.setSwitchTime(0.2f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == STATE::GROUND_SAFE) {
		setTexture("./assets/aldeanos/fatbird/GroundSafe(40x48).png");
		_animation.setImageCount(sf::Vector2u(4, 1));
		_animation.setSwitchTime(0.2f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == STATE::FALLING_SAFE) {
		setTexture("./assets/aldeanos/fatbird/FallSafe(40x48).png");
		_animation.setImageCount(sf::Vector2u(4, 1));
		_animation.setSwitchTime(0.12f);
		_animation.setImageUvRectSize(&_texture);
	}
}


void Fatbird::animationControl(float deltaTime) {  /// Control de tiempo por animacion

	if (_state == STATE::IDLE) {
		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 1.9f) { // 2.43segs Termina IDLE y extiende espinas
			if (_alive == true) {
				_state = STATE::FALLING;
				_body->SetGravityScale(1.0f);
				_body->SetAwake(true);
				_animationTimeCounter = 0;
				setAnimationState();
			}
		}

	}

	
	if (_state == STATE::GROUND) {

		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 3.78f) { // 2.43segs Terminan las espinas activas y comienza a retraerlas.
			if (_alive == true) {
				_dizzy = false;
				_state = STATE::IDLE;
				_contacting = false;
				_animationTimeCounter = 0;
				setAnimationState();
			}

		}

	}
	if (_state == STATE::HIT) {

		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 0.9f) { //0.37segs Termina de retraerlas y vuelve a estado inicial IDLE.
			if (_contacting == true) {
				_state = STATE::GROUND_SAFE;
				setAnimationState();
				_animationTimeCounter = 0;
			}
			else {
				_state = STATE::FALLING_SAFE;
				setAnimationState();
				_animationTimeCounter = 0;
			}
		
		}

	}
	

}
//***************SFML**************************/


//***************MOVIMIENTO, VELOCIDAD Y DIRECCION*******************************//

void Fatbird::move()
{
	_positionBody = getPositionBody();


	if (_state == STATE::IDLE && _dizzy == false) {
		_velocidad = 3.5f;
		///// SE GUARDA LA VELOCIDAD ACTUAL DE X E Y
		b2Vec2 velocidadActual = _body->GetLinearVelocity();
		///// SE PASA LA VELOCIDAD DE Y ACTUAL, Y LA NUEVA VELOCIDAD DE X (_velocidad esta seteado como propiedad de clase)
		_body->SetLinearVelocity(b2Vec2(velocidadActual.x, _velocidad));

	}

}

void Fatbird::setStateFloor() {
	_dizzy = true;
	if (_alive == true) {
	_state = STATE::GROUND;
	}
	else {
	_state = STATE::GROUND_SAFE;
	}
	_contacting = true;
	_animationTimeCounter = 0;
	setAnimationState();

}

void Fatbird::recibeDanio() {


	_alive = false;
	b2Filter filtro = _body->GetFixtureList()->GetFilterData();
	filtro.maskBits &= ~PLAYER;
	_body->GetFixtureList()->SetFilterData(filtro);
	_state = STATE::HIT;
	setAnimationState();
	_animationTimeCounter = 0;
}

void Fatbird::setContact(bool state)
{
	_contacting = state;
}
//***************MOVIMIENTO, VELOCIDAD Y DIRECCION*******************************//

//***************UPDATE Y DRAW****************************/

void Fatbird::updateVillager(int row, float deltaTime)
{
	//_positionBody = getPositionBody();
	move();
	animationControl(deltaTime);
	_sprite.setPosition(_positionBody.x * 40, 600 - _positionBody.y * 40);
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.getUvRect().width / 2.f, _animation.getUvRect().height / 2.f);
	_animation.Update(row, deltaTime);

}
void Fatbird::destroyBody(b2World& world)
{
	world.DestroyBody(_body);
	_body = nullptr;

}

Fatbird::~Fatbird() {
}
