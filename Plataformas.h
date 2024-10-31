#pragma once
#include "SFML/Graphics.hpp"
#include "Collisionable.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include <iostream>

class Plataformas : public sf::Drawable, public Collisionable {
private:
	sf::RectangleShape _shape;
	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
public:
	Plataformas(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world);
	void setPositionPlataforma(sf::Vector2f newPosition);
	void setBodyInWorld(b2World &world);
	void setSizeBody(sf::Vector2f newSize);
	void setFixture();
	void getPositionBody();

	void printRectangle(sf::Vector2f newSize);

	sf::RectangleShape getShape();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::FloatRect getBounds() const override;
	Plataformas();
	~Plataformas();

};