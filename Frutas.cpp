#include "Frutas.h"
#include <iostream>


Frutas::Frutas(b2World &world)
{
	setRandomFruit();
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
	_fixture = _body->CreateFixture(&_fixtureDef);
}

void Frutas::setTextureFruit(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Frutas::setPositionFruit(sf::Vector2f newPosition)
{
	_sprite.setPosition(newPosition.x * 40, 600 - newPosition.y * 40);

}

void Frutas::setAnimationState()
{

	///MANZANA, BANANA, FRUTILLA, KIWI, NARANJA, CEREZA, MELON, ANANA, FRUTA_RECOLECTADA

	if (frutaTipo == MANZANA) {
		setTextureFruit("./assets/frutas/Manzana.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.02f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (frutaTipo == BANANA) {
		setTextureFruit("./assets/frutas/Banana.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (frutaTipo == FRUTILLA) {
		setTextureFruit("./assets/frutas/Frutilla.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (frutaTipo == KIWI) {
		setTextureFruit("./assets/frutas/Kiwi.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (frutaTipo == NARANJA) {
		setTextureFruit("./assets/frutas/Naranja.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (frutaTipo == CEREZA) {
		setTextureFruit("./assets/frutas/Cereza.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (frutaTipo == ANANA) {
		setTextureFruit("./assets/frutas/Anana.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (frutaTipo == MELON) {
		setTextureFruit("./assets/frutas/Melon.png");
		_animation.setImageCount(sf::Vector2u(17, 1));
		_animation.setSwitchTime(0.04f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (frutaTipo == FRUTA_RECOLECTADA) {
		setTextureFruit("./assets/frutas/Recolectada.png");
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
	std::cout << " random x: " << randomX << " y el random y: " << randomY<<std::endl;
	setPositionBody(sf::Vector2f(randomX, randomY));
	setPositionFruit(sf::Vector2f(randomX,randomY));

}

void Frutas::setRandomFruit()
{
	///MANZANA, BANANA, FRUTILLA, KIWI, NARANJA, CEREZA, MELON, ANANA, FRUTA_RECOLECTADA

	int random = rand() % 8 + 1;

	switch (random){
	case 1:
		frutaTipo = FRUIT_TYPE::MANZANA;
		setAnimationState();
		break;
	case 2:
		frutaTipo = FRUIT_TYPE::BANANA;
		setAnimationState();
		break;
	case 3:
		frutaTipo = FRUIT_TYPE::FRUTILLA;
		setAnimationState();
		break;
	case 4:
		frutaTipo = FRUIT_TYPE::KIWI;
		setAnimationState();
		break;
	case 5:
		frutaTipo = FRUIT_TYPE::NARANJA;
		setAnimationState();
		break;
	case 6:
		frutaTipo = FRUIT_TYPE::CEREZA;
		setAnimationState();
		break;
	case 7:
		frutaTipo = FRUIT_TYPE::MELON;
		setAnimationState();
		break;
	case 8:
		frutaTipo = FRUIT_TYPE::ANANA;
		setAnimationState();
		break;
	default:
		break;
	}

}

void Frutas::setRectTextureAnimated()
{
	_sprite.setTextureRect(_animation.uvRect);

}

void Frutas::fruitUpdate(int row, float deltaTime)
{
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	_animation.Update(row, deltaTime);
}

void Frutas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}

sf::FloatRect Frutas::getBounds() const//*
{
	return _sprite.getGlobalBounds();
}


Frutas::~Frutas()
{
}
