#include "Rino.h"


Rino::Rino(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float pixelMetro) :Aldeano(newPosition, newVelocity, pixelMetro)
{
	_animationState = Rino_STATE::RUN;
	_directionR= true;
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

}
//***************BOX2D****************************/

void Rino::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DEL CUERPO

	_bodyDef.position.Set(newPosition.x, newPosition.y);
	_bodyDef.type = b2_dynamicBody;
}

void Rino::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);


	/////////asgina a travez de un puntero el objeto al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Rino::setSizeBody(sf::Vector2f newSize)
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(newSize.x, newSize.y);
}

void Rino::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 1.0f;   // DENSISDAD
	_fixtureDef.friction = 0.3f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = RINO;
	_fixtureDef.filter.maskBits = WALL | PLAYER | PLATFORM;

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 Rino::getPositionBody()
{
	b2Vec2 position = _body->GetPosition();
	return position;
}

//***************BOX2D****************************/

//***************SFML**************************/

void Rino::SetTextureRectAnimated() {
	_sprite.setTextureRect(_animation.uvRect);

}

void Rino::setAnimationState() {


	if (_animationState == Rino_STATE::IDLE) {
		setTexture("./assets/aldeanos/Rino/Idle(52x34).png");
		_animation.setImageCount(sf::Vector2u(11, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_animationState == Rino_STATE::IDLE_RESTORED) {
		setTexture("./assets/aldeanos/Rino/Spikesout(44x26).png");
		_animation.setImageCount(sf::Vector2u(11, 1));
		_animation.setSwitchTime(0.12f);
		_animation.setImageUvRectSize(&_texture);

	}
	if (_animationState == Rino_STATE::HIT) {
		setTexture("./assets/aldeanos/Rino/Hit(52x34).png");
		_animation.setImageCount(sf::Vector2u(5, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);

	}
	if (_animationState == Rino_STATE::HIT_WALL) {
		setTexture("./assets/aldeanos/Rino/Hit_Wall(52x34).png");
		_animation.setImageCount(sf::Vector2u(4, 1));
		_animation.setSwitchTime(0.12f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_animationState == Rino_STATE::RUN) {
		
		setTexture("./assets/aldeanos/Rino/Run(52x34).png");
		_animation.setImageCount(sf::Vector2u(6, 1));
		_animation.setSwitchTime(0.05f);
		_animation.setImageUvRectSize(&_texture);
		

	}

}

void Rino::animationControl(float deltaTime) {  /// Control de tiempo por animacion

	if (_animationState == Rino_STATE::IDLE) {

		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 1.3f) {
			_animationState = Rino_STATE::RUN;
			_dizzy = false;
			_animationTimeCounter = 0;
			setAnimationState();
		}
	}
	else if (_animationState == Rino_STATE::HIT_WALL) {

		_animationTimeCounter += deltaTime;
		if (_animationTimeCounter >= 0.4f) {
			_animationState = Rino_STATE::IDLE;
			_animationTimeCounter = 0;
			setAnimationState();
		}
	}

}

//***************SFML**************************/

void Rino::setNewDirectionR()
{
	_dizzy = true;
	_directionL = false;
	_directionR = true;
	_animationState = Rino_STATE::HIT_WALL;
	setAnimationState();
}
void Rino::setNewDirectionL()
{
	_dizzy = true;
	_directionL = true;
	_directionR = false;
	_animationState = Rino_STATE::HIT_WALL;
	setAnimationState();
}


void Rino::move(float velocidad)
{
	_positionBody = getPositionBody();

	if (_dizzy == false) {
		if (_directionR == true) {
			_velocidad = 4.5;
			_sprite.setScale(-1, 1);
		}
		else if (_directionL == true) {
			_velocidad = -4.5;
			_sprite.setScale(1, 1);
		}
	}
	
	///// SE GUARDA LA VELOCIDAD ACTUAL DE X E Y
	b2Vec2 velocidadActual = _body->GetLinearVelocity();
	///// SE PASA LA VELOCIDAD DE Y ACTUAL, Y LA NUEVA VELOCIDAD DE X (_velocidad esta seteado como propiedad de clase)
	_body->SetLinearVelocity(b2Vec2(_velocidad, velocidadActual.y));
}

void Rino::updateVillager(int row, float deltaTime)
{

	move(2.0f);
	animationControl(deltaTime);
	_sprite.setPosition(_positionBody.x * 40, 600 - _positionBody.y * 40);
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.getUvRect().width / 2.f, _animation.getUvRect().height / 2.f);
	_animation.Update(row, deltaTime);

}

void Rino::destroyBody(b2World& world)
{
	world.DestroyBody(_body);
}


Rino::~Rino() {

}