#pragma once
#include "Enemigo.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "CollisionCategories.h"


enum AnimationState {
	IDLE_BASIC, HIT_WALL
};

class Skull : public Enemigo {

private:
	AnimationState _animationState;
	float _animationTimeCounter = 0;
	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;

public:
	Skull(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float pixelMetro);
	void setPositionBody(sf::Vector2f newPosition);
	void setBodyInWorld(b2World& world);
	void setSizeBody(sf::Vector2f newSize);
	void setFixture();
	b2Vec2 getPositionBody();
	void move();
	void SetTextureRectAnimated();
	void setAnimationState();
	void animationControl(float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateEnemie(int row, float deltaTime) override;
	sf::Sprite getSpriteSkull();
	Skull();
	~Skull();
};


