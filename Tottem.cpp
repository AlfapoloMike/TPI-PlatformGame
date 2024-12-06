#include "Tottem.h"


Tottem::Tottem(b2World& world, int pixelMetro)
{
	setRandomPosition();
	setBodyInWorld(world);
	_positionBody = _body->GetPosition();
	setSizeBody();
	setFixture();
	setAnimationState();
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	_sprite.setPosition(_positionBody.x * pixelMetro, 600 - (_positionBody.y * pixelMetro));
	//_sprite.setScale(1.2, 1.5);
}



//***************BOX2D****************************/


void Tottem::setRandomPosition() {

	int maxX = 31.5, minX = 4;
	int maxY = 20, minY = 4;
	float randomX = (float)(rand() % (maxX - minX + 1) + minX);
	float randomY = (float)(rand() % (maxY - minY + 1) + minY);



	if (randomX >= 20 && randomX <= 22 && randomY >= 2.5 && randomY <= 11) {
		std::cout << "Debe cambiar de posicion " << std::endl;
		setRandomPosition();

	}
	else if (randomX >= 1.0 && randomX <= 16.5 && randomY >= 15 && randomY < 18.5) {
		std::cout << "Debe cambiar de posicion " << std::endl;
		setRandomPosition();
	}
	else {

		_bodyDef.position.Set(randomX, randomY);
		_bodyDef.type = b2_dynamicBody;

	}

}

void Tottem::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);

	/////////asgina a travez de un puntero el objeto conejo al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	////// Asignamos una escala de gravedad 0 para que no sea afectado por la gravedad.

	_body->SetLinearVelocity(b2Vec2(_velocidad.x, _velocidad.y));


}

void Tottem::setSizeBody()
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(0.375f, 0.4375f);
}

void Tottem::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 100000.0f;   // DENSISDAD
	_fixtureDef.friction = 0.5f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = TOTTEMS;
	_fixtureDef.filter.maskBits = WALL | PLATFORM;

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 Tottem::getPositionBody()
{
	_positionBody = _body->GetPosition();
	return _positionBody;
}
//***************BOX2D****************************/

void Tottem::setTexture(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Tottem::SetTextureRectAnimated() {

	_sprite.setTextureRect(_animation.uvRect);

}

void Tottem::setAnimationState()
{
	if (_state == TOTTEM_STATE::SPAWNING) {
		setTexture("./assets/mago/TottemSpawning.png");
		_animation.setImageCount(sf::Vector2u(5, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == TOTTEM_STATE::ACTIVE) {
		setTexture("./assets/mago/TottemIdle.png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);

	}
	else if (_state == TOTTEM_STATE::HITTED) {
		setTexture("./assets/mago/TottemDestroy.png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == TOTTEM_STATE::DESTROYED) {
		setTexture("./assets/mago/TottemInvisible.png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == TOTTEM_STATE::PRESPAWN) {
		setTexture("./assets/mago/TottemInvisible.png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}

}

void Tottem::animationControl(float deltaTime) {
	///_animationTimer

	if (_state == TOTTEM_STATE::SPAWNING) {
		_animationTimer += deltaTime;
		if (_animationTimer >= 0.4f) {

			_animationTimer = 0;

			b2Filter filtro = _body->GetFixtureList()->GetFilterData();
			filtro.maskBits |= PLAYER;
			_body->GetFixtureList()->SetFilterData(filtro);

			_state = TOTTEM_STATE::ACTIVE;
						setAnimationState();
		}
	}
	else if (_state == TOTTEM_STATE::HITTED) {
		_animationTimer += deltaTime;
		if (_animationTimer >= 0.8f) {
			_animationTimer = 0;
			_state = TOTTEM_STATE::DESTROYED;
			_isDestroyed = true;
			setAnimationState();
		}
	}

}

void Tottem::Update(int row, float deltaTime, b2World& world) {

	_positionBody = _body->GetPosition();
	animationControl(deltaTime);
	_sprite.setPosition(_positionBody.x * 40, 600 - (_positionBody.y * 40));
	_sprite.setTextureRect(_animation.uvRect);
	_animation.Update(row, deltaTime);


}

void Tottem::setDestroyed() {


	_state = TOTTEM_STATE::HITTED;
	setAnimationState();

	b2Filter filtro = _body->GetFixtureList()->GetFilterData();
	filtro.maskBits &= ~PLAYER;
	_body->GetFixtureList()->SetFilterData(filtro);

}

void Tottem::setSpawning() {

	_state = TOTTEM_STATE::SPAWNING;
	setAnimationState();

}


bool Tottem::isDestroyed() {
	return _isDestroyed;
}

void Tottem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(_sprite, states);


}

void Tottem::destroyBody(b2World& world)
{
	if (_body != nullptr) {
		world.DestroyBody(_body);
		_body = nullptr;
	}
}

Tottem::~Tottem()
{
}
