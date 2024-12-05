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
	_sprite.setScale(1.2, 1.2);
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
	_bodyBox.SetAsBox(0.25f,0.25f);

}

void Frutas::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.friction = 0.2f;
	_fixtureDef.density = 0.3f;
	_fixtureDef.isSensor = true;
	
	_fixtureDef.filter.categoryBits = FRUITS; // Categoría del muro
	_fixtureDef.filter.maskBits = PLAYER | FRUITS;   // Colisiona solo con el personaje

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
	//16x
	//11y
	int maxX = 32.5, minX = 4;
	int maxY = 20, minY = 4;
	float randomX = (float)(rand() % (maxX - minX + 1) + minX);
	float randomY = (float)(rand() % (maxY - minY + 1) + minY);

	///_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(20.75f, 6.5f), sf::Vector2f(0.5f, 3.75f), world, false));
	///_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(8.75f, 17.0f), sf::Vector2f(7.15f, 0.85f), world, false));

	
	if (randomX >= 20 && randomX <= 22 && randomY >= 2.5 && randomY <= 11) {
		std::cout << "Debe cambiar de posicion " << std::endl;
		setRandomPosition();

	}
	else if (randomX >= 1.0 && randomX <= 16.5 && randomY >= 15 && randomY < 18.5) {
		std::cout << "Debe cambiar de posicion " << std::endl;

		setRandomPosition();
	}
	else {

	setPositionBody(sf::Vector2f(randomX, randomY));
	setPositionFruit(sf::Vector2f(randomX,randomY));

	}



}

void Frutas::setRandomFruit()
{
	///MANZANA, BANANA, FRUTILLA, KIWI, NARANJA, CEREZA, MELON, ANANA, FRUTA_RECOLECTADA

	int random = rand() % 8 + 1;


	if (random == 1) {
		frutaTipo = FRUIT_TYPE::MANZANA;
		_fruitType = 1;
		_points = 100;
	}
	else if (random == 2) {
		frutaTipo = FRUIT_TYPE::BANANA;
		_fruitType = 2;
		_points = 50;

	}
	else if (random == 3) {
		frutaTipo = FRUIT_TYPE::FRUTILLA;
		_fruitType = 3;
		_points = 150;

	}
	else if (random == 4) {
		frutaTipo = FRUIT_TYPE::KIWI;
		_fruitType = 4;
		_points = 70;

	}
	else if (random == 5) {
		frutaTipo = FRUIT_TYPE::NARANJA;
		_fruitType = 5;
		_points = 30;

	}
	else if (random == 6) {
		frutaTipo = FRUIT_TYPE::CEREZA;
		_fruitType = 6;
		_points = 30;

	}
	else if (random == 7) {
		frutaTipo = FRUIT_TYPE::MELON;
		_fruitType = 7;
		_points = 110;

	}
	else if (random == 8) {
		frutaTipo = FRUIT_TYPE::ANANA;
		_fruitType = 8;
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

int Frutas::getFruitType() {
	return _fruitType;
}

void Frutas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}

void Frutas::destroyBody(b2World& world)
{	
	if (_body != nullptr) {
		world.DestroyBody(_body);

	}
}

Frutas::~Frutas()
{
}
