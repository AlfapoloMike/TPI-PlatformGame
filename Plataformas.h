#pragma once
#include "SFML/Graphics.hpp"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "CollisionCategories.h"
#include <iostream>

class Plataformas : public sf::Drawable {
private:
	sf::RectangleShape _shape;
	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	float _bordeDer=0, _bordeIzq=0;
public:
	Plataformas(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, bool tipo);
	void setPositionPlataforma(sf::Vector2f newPosition);
	void setBodyInWorld(b2World &world);
	void setSizeBody(sf::Vector2f newSize);
	void setFixture(bool tipo);
	void getPositionBody();
	void setBordes(sf::Vector2f newPosition, sf::Vector2f newSize);

	b2Vec2 getBorder()const;

	void printRectangle(sf::Vector2f newPosition, sf::Vector2f newSize);

	sf::RectangleShape getShape();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void destroyBody(b2World& world);
	Plataformas();
	~Plataformas();

};