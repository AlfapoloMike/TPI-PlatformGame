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
	b2Vec2 _positionBody;
	sf::Vector2f _velocidad = sf::Vector2f(2.5f,2.5f);

public:
	Skull(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float pixelMetro);
	void setPositionBody(sf::Vector2f newPosition);
	void setBodyInWorld(b2World& world);
	void setSizeBody(sf::Vector2f newSize);
	void setFixture();
	b2Vec2 getPositionBody();
	void setNewDirection(bool horizontalContact, bool verticalContact);
	void SetTextureRectAnimated();
	void setAnimationState();
	void animationControl(float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateEnemie(int row, float deltaTime) override;
	sf::Sprite getSpriteSkull();
	void destroyBody(b2World& world);
	~Skull();
};


