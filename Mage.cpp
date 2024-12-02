#include "Mage.h"



Mage::Mage(b2World& world,sf::Vector2f position, int pixelMetro)
{
	setPositionBody(position);
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


void Mage::setPositionBody(sf::Vector2f position) {

		_bodyDef.position.Set(position.x, position.y);
		_bodyDef.type = b2_dynamicBody;

}

void Mage::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);

	/////////asgina a travez de un puntero el objeto conejo al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	////// Asignamos una escala de gravedad 0 para que no sea afectado por la gravedad.

	_body->SetLinearVelocity(b2Vec2(_velocidad.x, _velocidad.y));


}

void Mage::setSizeBody()
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(0.375f, 0.4375f);
}

void Mage::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 100000.0f;   // DENSISDAD
	_fixtureDef.friction = 0.5f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = MAGE;
	_fixtureDef.filter.maskBits = WALL | PLATFORM | PLAYER;

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 Mage::getPositionBody()
{
	_positionBody = _body->GetPosition();
	return _positionBody;
}
//***************BOX2D****************************/

void Mage::setTexture(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Mage::SetTextureRectAnimated() {

	_sprite.setTextureRect(_animation.uvRect);

}

void Mage::setAnimationState()
{
	/*
	if (_state == TOTTEM_STATE::SPAWNING) {
		setTexture("./assets/mago/TottemSpawning.png");
		_animation.setImageCount(sf::Vector2u(5, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	*/


}

void Mage::animationControl(float deltaTime) {
	///_animationTimer
	/*
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
	*/

}

void Mage::Update(int row, float deltaTime, b2World& world) {

	_positionBody = _body->GetPosition();
	animationControl(deltaTime);
	_sprite.setPosition(_positionBody.x * 40, 600 - (_positionBody.y * 40));
	_sprite.setTextureRect(_animation.uvRect);
	_animation.Update(row, deltaTime);


}

void Mage::setDestroyed() {


}

void Mage::setSpawning() {



}

bool Mage::isDestroyed() {
	return _isDestroyed;
}

void Mage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(_sprite, states);


}


Mage::~Mage()
{
}
