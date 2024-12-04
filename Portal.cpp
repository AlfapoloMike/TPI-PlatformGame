#include "Portal.h"

Portal::Portal(sf::Vector2f newPosition,b2World& world,float pixelMetro)
{
	_state = PORTAL_STATE::SPAWNING;

	setPositionBody(newPosition);
	setBodyInWorld(world);
	setSizeBody();
	setFixture();
	setAnimationState();
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	_sprite.setPosition(sf::Vector2f(newPosition.x * pixelMetro, 600 - newPosition.y * pixelMetro));

}




//***************BOX2D****************************/

void Portal::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DEL CUERPO
	_bodyDef.position.Set(newPosition.x, newPosition.y);
	_bodyDef.type = b2_dynamicBody;
}



void Portal::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);


	/////////asgina a travez de un puntero el objeto conejo al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Portal::setSizeBody()
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(0.4f, 0.6f);

}

void Portal::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 1.0f;   // DENSISDAD
	_fixtureDef.friction = 0.3f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = PORTAL;
	_fixtureDef.filter.maskBits = PLAYER | PLATFORM;

	_fixture = _body->CreateFixture(&_fixtureDef);


}

b2Vec2 Portal::getPositionBody()
{
	b2Vec2 position = _body->GetPosition();
	return position;
}

//***************BOX2D****************************/



void Portal::setTexture(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Portal::SetTextureRectAnimated() {

	_sprite.setTextureRect(_animation.uvRect);

}

void Portal::setAnimationState()
{


	if (_state == PORTAL_STATE::DESACTIVADO) {
		setTexture("./assets/map/PortalDesactivado.png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == PORTAL_STATE::SPAWNING) {
		setTexture("./assets/map/PortalSpawn.png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (_state == PORTAL_STATE::IDLE) {
		setTexture("./assets/map/PortalIdle.png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}


}

void Portal::animationControl(float deltaTime) {

	if (_state == PORTAL_STATE::SPAWNING) {
		animationTimer += deltaTime;
		if (animationTimer >= 0.4f) {
			_state = PORTAL_STATE::IDLE;
			setAnimationState();
			animationTimer = 0;
		}
	}

}

void Portal::Update(int row, float deltaTime) {

	b2Vec2 position = _body->GetPosition();

	animationControl(deltaTime);
	_sprite.setPosition(sf::Vector2f(position.x * 40, 600 - position.y * 40));
	_sprite.setTextureRect(_animation.uvRect);
	_animation.Update(row, deltaTime);

}

void Portal::setTouched()
{
	touched = true;
}

bool Portal::isTouched()
{
	return touched;
}
void Portal::destroyBody(b2World& world)
{
	world.DestroyBody(_body);
}



void Portal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}