#pragma once
#include "SFML/Graphics.hpp"
#include "Collisionable.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include <iostream>

class Plataformas : public sf::Drawable, public Collisionable {
private:
	sf::RectangleShape _shape;
	b2BodyDef _plataformaDef;
	b2Body* _groundBody;
	b2PolygonShape _groundBox;
public:
	Plataformas(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world);
	void setPositionPlataforma(sf::Vector2f newPosition);
	void setBodyInWorld(b2World &world);
	void setSizePlataforma(sf::Vector2f newSize);
	void setDensity();
	void getPositionBody();

	void printRectangle(sf::Vector2f newSize);

	sf::RectangleShape getShape();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::FloatRect getBounds() const override;
	Plataformas();
	~Plataformas();

};