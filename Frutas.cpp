#include "Frutas.h"
#include <iostream>


Frutas::Frutas()
{
	setRandomFruit();
	_sprite.setOrigin(_animation.getUvRect().width / 2.0, _animation.getUvRect().height/2.0);
	setRandomPosition();
	_sprite.setScale(1.4, 1.4);
}

void Frutas::setTextureFruit(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Frutas::setPositionFruit(sf::Vector2f newPosition)
{
	_sprite.setPosition(sf::Vector2f(newPosition.x, newPosition.y));

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
	int randomX = rand() % 600 + 100;
	int randomY = rand() % 500 + 100;

	setPositionFruit(sf::Vector2f(randomX, randomY));

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
	_sprite.setOrigin(_animation.getUvRect().width / 2.0, _animation.getUvRect().height / 2.0);
	_animation.Update(row, deltaTime);
}

void Frutas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}


Frutas::~Frutas()
{
}
