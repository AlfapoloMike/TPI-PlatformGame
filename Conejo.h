#pragma once
#include "Enemigo.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Animation.h"

enum STATES {
	RUN_R, RUN_L, HIT
};

class Conejo : public Enemigo {

	/********************/
public:
	Conejo(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float limiteIzq, float limiteDer, float pixelMetro);
	void moveEnemy();
	void setPositionBody(sf::Vector2f newPosition);
	void setBodyInWorld(b2World& world);
	void setSizeBody(sf::Vector2f newSize);
	void setFixture();
	b2Vec2 getPositionBody();
	void updateEnemie(int row, float deltaTime) override;
	void SetTextureRectAnimated();
	void setAnimationState();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~Conejo();

	//// Box2D GENERACION
private:
	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2FixtureDef _fixtureDef;
	float _velocidad = 2.0f;
	float _limiteIzq, _limiteDer;
	STATES _estado = STATES::RUN_R;
	/********************/

};

