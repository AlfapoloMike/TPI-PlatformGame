#pragma once
#include "Aldeano.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include <SFML/Graphics.hpp>


enum class STATE {
	FALLING,
	GROUND,
	HIT,
	IDLE,
};


class Fatbird : public Aldeano {


private:


	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	float _velocidad = 0.0f;
	/// en principio los limites tienen que ser el ancho de pantalla
	// al tocar la plataforma donde aparece, los limites se re-setean
	float _limiteIzq = 0.0f, _limiteDer = 20.0f;
	b2Vec2 _positionBody;
	bool _contacting = false;
	float _animationTimeCounter = 0;
	bool _dizzy = false;
	bool _alive = true;
	STATE _state = STATE::IDLE;

public:
	Fatbird(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float pixelMetro);

	void setPositionBody(sf::Vector2f newPosition);

	void setBodyInWorld(b2World& world);

	void setSizeBody(sf::Vector2f newSize);

	void setFixture();

	void SetTextureRectAnimated();

	void setAnimationState();

	void animationControl(float deltaTime);

	void setStateFloor();

	void updateVillager(int row, float deltaTime);

	void setContact(bool state);

	b2Vec2 getPositionBody();

	void move();

	~Fatbird();
};