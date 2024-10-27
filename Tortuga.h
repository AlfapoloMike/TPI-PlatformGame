#pragma once
#include "Aldeano.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"

class Tortuga : public Aldeano {

public:
	Tortuga(sf::Vector2f newPosition, sf::Vector2f newVelocity);
	void update(int row, float deltaTime);
	//void move(); Tortuga no se mueve
	void SetTextureRectAnimated();
	void setAnimationState();
	void animationControl();
	~Tortuga();

	void setPositionBody(sf::Vector2f newPosition);
	void setBodyInWorld(b2World& world);
	void setSizeBody(sf::Vector2f newSize);
	void setFixture();
	void getPositionBody();
	void moveEnemy(float velocidad);

private:
	enum AnimationState {
		ESPINAS_EXT,
		ESPINAS_RET,
		ESPINAS_IDLE,
		IDLE
	};

	AnimationState _animationState;
	float _animationTimeCounter = 0;
	bool _espinas;


	/********************/
	//// Box2D GENERACION

	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2FixtureDef _fixtureDef;
	b2Vec2 _velocidad;
	/********************/
};

