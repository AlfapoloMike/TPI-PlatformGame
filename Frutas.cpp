#include "Frutas.h"
#include <iostream>


Frutas::Frutas(b2World &world)
{
	setRandomFruit();
	setTextureFruit();
	setAnimationState();
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	setRandomPosition();
	setBodyInWorld(world);
	setSizeBody();
	setFixture();
}


void Frutas::setPositionBody(sf::Vector2f newPosition)
{
	_bodyDef.type = b2_staticBody;
	_bodyDef.position.Set(newPosition.x, newPosition.y);

}

void Frutas::setBodyInWorld(b2World& world)
{
	_body = world.CreateBody(&_bodyDef);
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

}

void Frutas::setSizeBody()
{
	_bodyBox.SetAsBox(0.2f,0.2f);

}

void Frutas::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.friction = 0.2f;
	_fixtureDef.density = 0.3f;
	_fixtureDef.isSensor = true;
	
	_fixtureDef.filter.categoryBits = FRUITS; // Categoría del muro
	_fixtureDef.filter.maskBits = PLAYER;   // Colisiona solo con el personaje

	_fixture = _body->CreateFixture(&_fixtureDef);
}

void Frutas::setTextureFruit()
{
	/*
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
	*/

	if (frutaTipo == MANZANA) {

		_texture.loadFromFile("./assets/frutas/Manzana.png");
		_sprite.setTexture(_texture);

	}
	else if (frutaTipo == BANANA) {

		_texture.loadFromFile("./assets/frutas/Banana.png");
		_sprite.setTexture(_texture);
	}
	else if (frutaTipo == FRUTILLA) {

		_texture.loadFromFile("./assets/frutas/Frutilla.png");
		_sprite.setTexture(_texture);

	}
	else if (frutaTipo == KIWI) {

		_texture.loadFromFile("./assets/frutas/Kiwi.png");
		_sprite.setTexture(_texture);
	}
	else if (frutaTipo == NARANJA) {
		_texture.loadFromFile("./assets/frutas/Naranja.png");
		_sprite.setTexture(_texture);
	}
	else if (frutaTipo == CEREZA) {

		_texture.loadFromFile("./assets/frutas/Cereza.png");
		_sprite.setTexture(_texture);
	}
	else if (frutaTipo == ANANA) {
		_texture.loadFromFile("./assets/frutas/Anana.png");
		_sprite.setTexture(_texture);
	}
	else if (frutaTipo == MELON) {

		_texture.loadFromFile("./assets/frutas/Melon.png");
		_sprite.setTexture(_texture);
	}
	else if (frutaTipo == PICKED) {
		_texture.loadFromFile("./assets/frutas/Recolectada.png");
		_sprite.setTexture(_texture);
	}

}

void Frutas::setPositionFruit(sf::Vector2f newPosition)
{
	_sprite.setPosition(newPosition.x * 40, 600 - newPosition.y * 40);

}

void Frutas::setAnimationState()
{

	///MANZANA, BANANA, FRUTILLA, KIWI, NARANJA, CEREZA, MELON, ANANA, FRUTA_RECOLECTADA

	if (frutaTipo == MANZANA) {
		//setTextureFruit("./assets/frutas/Manzana.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.02f);
		_animation.setImageUvRectSize(&_texture);
	}else if (frutaTipo == BANANA) {
		//setTextureFruit("./assets/frutas/Banana.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (frutaTipo == FRUTILLA) {
		//setTextureFruit("./assets/frutas/Frutilla.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (frutaTipo == KIWI) {
	//	setTextureFruit("./assets/frutas/Kiwi.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (frutaTipo == NARANJA) {
	//	setTextureFruit("./assets/frutas/Naranja.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (frutaTipo == CEREZA) {
		//setTextureFruit("./assets/frutas/Cereza.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (frutaTipo == ANANA) {
	//	setTextureFruit("./assets/frutas/Anana.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if (frutaTipo == MELON) {
		//setTextureFruit("./assets/frutas/Melon.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	else if(frutaTipo == PICKED) {
		//setTextureFruit("./assets/frutas/Recolectada.png");
		_animation.setImageCount(sf::Vector2u(6, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}

	

}

void Frutas::setRandomPosition()
{
	int maxX = 16, minX = 4;
	int maxY = 11, minY = 4;
	float randomX = (float)(rand() % (maxX - minX + 1) + minX);
	float randomY = (float)(rand() % (maxY - minY + 1) + minY);
	setPositionBody(sf::Vector2f(randomX, randomY));
	setPositionFruit(sf::Vector2f(randomX,randomY));

}

void Frutas::setRandomFruit()
{
	///MANZANA, BANANA, FRUTILLA, KIWI, NARANJA, CEREZA, MELON, ANANA, FRUTA_RECOLECTADA

	int random = rand() % 8 + 1;


	if (random == 1) {
		frutaTipo = FRUIT_TYPE::MANZANA;
		_points = 100;
	}
	else if (random == 2) {
		frutaTipo = FRUIT_TYPE::BANANA;
		_points = 50;

	}
	else if (random == 3) {
		frutaTipo = FRUIT_TYPE::FRUTILLA;
		_points = 150;

	}
	else if (random == 4) {
		frutaTipo = FRUIT_TYPE::KIWI;
		_points = 70;

	}
	else if (random == 5) {
		frutaTipo = FRUIT_TYPE::NARANJA;
		_points = 30;

	}
	else if (random == 6) {
		frutaTipo = FRUIT_TYPE::CEREZA;
		_points = 30;

	}
	else if (random == 7) {
		frutaTipo = FRUIT_TYPE::MELON;
		_points = 110;

	}
	else if (random == 8) {
		frutaTipo = FRUIT_TYPE::ANANA;
		_points = 70;

	}

}

void Frutas::setRectTextureAnimated()
{
	_sprite.setTextureRect(_animation.uvRect);

}

void Frutas::animationControl(float deltaTime) {

	if (frutaTipo == PICKED) {
		_animationTimer += deltaTime;
		if (_animationTimer >= 0.45f) {
			_picked = true;
		}
	}
}

void Frutas::fruitUpdate(int row, float deltaTime)
{
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	animationControl(deltaTime);
	_animation.Update(row, deltaTime);
}

void Frutas::setFruitPicked()
{
	b2Filter filtro = _body->GetFixtureList()->GetFilterData();
	filtro.maskBits &= ~PLAYER;
	_body->GetFixtureList()->SetFilterData(filtro);

	frutaTipo = PICKED;
	setTextureFruit();
	setAnimationState();
}

int Frutas::getPoints()
{

	return _points;
}

bool Frutas::getPickedState()
{
	return _picked;
}



void Frutas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}

sf::FloatRect Frutas::getBounds() const
{
	return _sprite.getGlobalBounds();
}


Frutas::~Frutas()
{
}
