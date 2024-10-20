#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <stdlib.h>
#include <time.h>

enum FRUIT_TYPE {
	MANZANA, BANANA, FRUTILLA, KIWI, NARANJA, CEREZA, MELON, ANANA, FRUTA_RECOLECTADA 
};

class Frutas : public sf::Drawable{
protected:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	Animation _animation;
	FRUIT_TYPE frutaTipo;
public:
	Frutas();
	void setTextureFruit(std::string texture);
	void setPositionFruit(sf::Vector2f newPosition);
	void setAnimationState();
	void setRandomPosition();
	void setRandomFruit();
	void setRectTextureAnimated();
	void fruitUpdate(int row, float deltaTime);
	//sf::Sprite getSprite();
	//sf::Texture getTexture();
	//sf::Vector2f getPosition();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~Frutas();
};