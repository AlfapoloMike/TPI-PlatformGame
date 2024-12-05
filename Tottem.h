#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "CollisionCategories.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

enum class TOTTEM_STATE {
	PRESPAWN,
	SPAWNING,
	ACTIVE,
	HITTED,
	DESTROYED
};

class Tottem : public sf::Drawable {

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::Vector2f _size;
	Animation _animation;
	TOTTEM_STATE _state= TOTTEM_STATE::PRESPAWN;

	float _animationTimer = 0;

	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	b2Vec2 _positionBody;
	sf::Vector2f _velocidad = sf::Vector2f(0.0f, 2.5f);


	bool _isDestroyed = false;

public:

	Tottem(b2World& world, int pixelMetro);

	void setRandomPosition();

	void setBodyInWorld(b2World& world);

	void setSizeBody();

	void setFixture();

	b2Vec2 getPositionBody();

	void setTexture(std::string texture);

	void SetTextureRectAnimated();

	void setAnimationState();

	void animationControl(float deltaTime);

	void Update(int row, float deltaTime, b2World& world);

	void setDestroyed();

	void setSpawning();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void destroyBody(b2World& world);

	bool isDestroyed();

	~Tottem();
};