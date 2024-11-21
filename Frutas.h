#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <stdlib.h>
#include <time.h>
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "CollisionCategories.h"


enum FRUIT_TYPE {
	MANZANA, BANANA, FRUTILLA, KIWI, NARANJA, CEREZA, MELON, ANANA, PICKED
};

class Frutas : public sf::Drawable {
protected:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	Animation _animation;
	FRUIT_TYPE frutaTipo;
	///BOX2D ATRIBUTOS
	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	bool _picked = false;
	float _animationTimer = 0;
	int _points;


public:
	Frutas(b2World &world);
	/////////BOX2D
	void setPositionBody(sf::Vector2f newPosition);
	void setBodyInWorld(b2World& world);
	void setSizeBody();
	void setFixture();
	//////// SFML
	void setTextureFruit();
	void setPositionFruit(sf::Vector2f newPosition);
	void setAnimationState();
	void setRandomPosition();
	void setRandomFruit();
	void setRectTextureAnimated();
	void animationControl(float deltaTime);
	void fruitUpdate(int row, float deltaTime);
	void setFruitPicked();

	int getPoints();
	bool getPickedState();

	//sf::Sprite getSprite();
	//sf::Texture getTexture();
	//sf::Vector2f getPosition();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~Frutas();
};