#include "Crystal.h"
#include <iostream>


Crystal::Crystal(sf::Vector2f newPosition, b2World& world,  int pixelMetro, int type, bool laserR)
{

	setType(type);
	setPositionBody(newPosition);
	setBodyInWorld(world);
	setSizeBody();
	setFixture();
	setAnimationState();
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	_sprite.setPosition(newPosition.x*pixelMetro, 600 - (newPosition.y*pixelMetro));
	_sprite.setScale(0.6, 0.6);

	if (_type == CRYSTAL_TYPE::LASER) {
	

		_laser = std::make_unique<Laser>(newPosition, pixelMetro, laserR);
		_laser->setSpritePosition(sf::Vector2f(newPosition.x * pixelMetro + (float)_animation.getUvRect().width * 5.5, 600 - newPosition.y * pixelMetro));

	}

	
}

void Crystal::setType(int type) {
	
	switch (type)
	{
	case 1:
		_type = CRYSTAL_TYPE::ICEBALL;
		break;
	case 2:
		_type = CRYSTAL_TYPE::LASER;
		break;
	default:
		break;
	}

}

//***************BOX2D****************************/
void Crystal::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DEL CUERPO

	if (_type == CRYSTAL_TYPE::ICEBALL) {
		//setRandomPosition();
		_bodyDef.position.Set(newPosition.x, newPosition.y);
		_bodyDef.type = b2_dynamicBody;
	}
	else if (_type == CRYSTAL_TYPE::LASER) {
		_bodyDef.position.Set(newPosition.x, newPosition.y);
		_bodyDef.type = b2_dynamicBody;
	}

}

void Crystal::setRandomPosition() {

	int maxX = 31.5, minX = 4;
	int maxY = 20, minY = 4;
	float randomX = (float)(rand() % (maxX - minX + 1) + minX);
	float randomY = (float)(rand() % (maxY - minY + 1) + minY);



	if (randomX >= 18 && randomX <= 23 && randomY >= 2.5 && randomY <= 20) {
		setRandomPosition();

	}
	else if (randomX >= 1.0 && randomX <= 16.5 && randomY >= 14 && randomY < 20.0) {
		setRandomPosition();
	}
	else {

		_bodyDef.position.Set(randomX, randomY);
		_bodyDef.type = b2_dynamicBody;

	}



}

void Crystal::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);

	/////////asgina a travez de un puntero el objeto conejo al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	////// Asignamos una escala de gravedad 0 para que no sea afectado por la gravedad.
	if (_type == CRYSTAL_TYPE::LASER) {
		_body->SetGravityScale(0.0f);
		_body->SetLinearVelocity(b2Vec2(_velocidad.x, _velocidad.y));

	}
	else if (_type == CRYSTAL_TYPE::ICEBALL) {
		_body->SetGravityScale(0.0f);
		_body->SetLinearVelocity(b2Vec2(_velocidad.x, 0));

	}
	

}

void Crystal::setSizeBody()
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(0.2f, 0.4f);
}

void Crystal::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 100000.0f;   // DENSISDAD
	_fixtureDef.friction = 0.5f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = CRYSTAL;
	if (_type == CRYSTAL_TYPE::LASER) {
		_fixtureDef.filter.maskBits = PLAYER | WALL;
	}
	else if (_type == CRYSTAL_TYPE::ICEBALL) {
		_fixtureDef.filter.maskBits = PLAYER | WALL | PLATFORM;

	}

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 Crystal::getPositionBody()
{
	_positionBody = _body->GetPosition();
	return _positionBody;
}
//***************BOX2D****************************/

void Crystal::setTexture(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Crystal::SetTextureRectAnimated() {

	_sprite.setTextureRect(_animation.uvRect);

}

void Crystal::setAnimationState()
{

	setTexture("./assets/mago/spells/Crystal.png");
	_animation.setImageCount(sf::Vector2u(6, 1));
	_animation.setSwitchTime(0.09f);
	_animation.setImageUvRectSize(&_texture);

}

void Crystal::Update(int row, float deltaTime, b2World& world) {
	

	if (_type == CRYSTAL_TYPE::LASER) {
		move();
		_positionBody = _body->GetPosition();

		sf::Vector2f _position;
		if (_laser->getSideR()) {
			_position.x = _positionBody.x - ((float)_animation.getUvRect().width * 5.5) / 40;
		}
		else {
			_position.x = _positionBody.x + ((float)_animation.getUvRect().width * 5.5) / 40;
		}
		_position.y = _positionBody.y;

		_sprite.setPosition(_positionBody.x * 40, 600 - (_positionBody.y * 40));
		_sprite.setTextureRect(_animation.uvRect);
		_animation.Update(row, deltaTime);
		_laser->Update(0, deltaTime, _position, world);
	}
	else if (_type == CRYSTAL_TYPE::ICEBALL) {

		_positionBody = _body->GetPosition();

		sf::Vector2f _position;
		_position.x = _positionBody.x + ((float)_animation.getUvRect().width * 5.5) / 40;
		_position.y = _positionBody.y;

		_sprite.setPosition(_positionBody.x * 40, 600 - (_positionBody.y * 40));


		spawnIceBall(world, deltaTime);

		for (int i = 0; i < _iceBall.size(); i++) {
			_iceBall[i]->Update(0, deltaTime, _position, world);
		}

		_sprite.setTextureRect(_animation.uvRect);
		_animation.Update(row, deltaTime);
	}

	
}



void Crystal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_type == CRYSTAL_TYPE::LASER) {
		target.draw(_laser->getShape(), states);
	}


	if (_type == CRYSTAL_TYPE::ICEBALL) {
		for (int i = 0; i < _iceBall.size(); i++) {
			target.draw(_iceBall[i]->getShape(), states);
		}
	}

	target.draw(_sprite, states);


}

void Crystal::move() {

	b2Vec2 velocidadActual = _body->GetLinearVelocity();
	
	if (_type == CRYSTAL_TYPE::ICEBALL) {
		_body->SetLinearVelocity(b2Vec2(velocidadActual.x, 0));


	}
	else {
		_body->SetLinearVelocity(b2Vec2(0, velocidadActual.y));

	}
}

void Crystal::changeDirection() {

	b2Vec2 velocidadActual = _body->GetLinearVelocity();
	if (_type == CRYSTAL_TYPE::ICEBALL) {
		_body->SetLinearVelocity(b2Vec2(velocidadActual.x *-1, 0));

	}
	else {
		_body->SetLinearVelocity(b2Vec2(0, velocidadActual.y*-1));
	}
}


void Crystal::spawnIceBall(b2World& world, float deltaTime)
{
	_positionBody = _body->GetPosition();

	if (_iceBall.size() < 3) {

		spawnTime += deltaTime;
		if (spawnTime > 1.0f) {
			_iceBall.push_back(std::make_unique<IceBall>(sf::Vector2f(_positionBody.x, _positionBody.y), 40, world));

			spawnTime = 0;

		}
	}

	for (int i = 0; i < _iceBall.size(); i++) {
		if (_iceBall[i]->Destroyed() == true) {
			_iceBall.erase(_iceBall.begin() + i);
			i--;
		}
	}

}

bool Crystal::isLaser()
{
	if (_type == CRYSTAL_TYPE::LASER) {

		return true;
	}
	else {
		return false;
	}
}

void Crystal::destroyBody(b2World& world)
{

	if (_type == CRYSTAL_TYPE::LASER) {
		if (_laser != nullptr) {
			_laser->destroyBody(world);
		}
	}


	if (_type == CRYSTAL_TYPE::ICEBALL) {
		for (int i = 0; i < _iceBall.size(); i++) {

			if (_iceBall[i] != nullptr) {
				_iceBall[i]->destroyBody(world);
			}
			
		}
	}

	_laser.reset();
	_iceBall.clear();

	if (_body != nullptr) {
		world.DestroyBody(_body);
	}
}

Crystal::~Crystal()
{

}
