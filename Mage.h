#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "CollisionCategories.h"
#include <iostream>

enum class MAGE_STATE {
	CASTING,
	IDLE,
	DEAD,
	SPAWN,
	CASTING_FINAL,
	SKILL,
	DYING,
};

class Mage : public sf::Drawable {


private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	sf::Vector2f _size;
	Animation _animation;
	bool _vida[12] = { true, true, true, true, true, true, true, true, true, true, true, true };

	float _animationTimer = 0;

	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	b2Vec2 _positionBody;
	sf::Vector2f _velocidad = sf::Vector2f(0.0f, 0.0f);

	MAGE_STATE _state = MAGE_STATE::CASTING_FINAL;

	bool _isDestroyed = false;

public:

	Mage(b2World& world, sf::Vector2f position, int pixelMetro);

	void setPositionBody(sf::Vector2f position);

	void setBodyInWorld(b2World& world);

	void setSizeBody();

	void setFixture();

	b2Vec2 getPositionBody();

	void setTexture(std::string texture);

	void SetTextureRectAnimated();

	void setAnimationState();

	void animationControl(float deltaTime);

	void Update(int row, float deltaTime, b2World& world);

	void damaged(bool damageIs);


	void checkLife();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool isDestroyed();

	~Mage();
};