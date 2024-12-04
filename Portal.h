#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "CollisionCategories.h"


enum class PORTAL_STATE {
	SPAWNING,
	IDLE,
	DESACTIVADO
};

class Portal : public sf::Drawable {

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	Animation _animation;
	///BOX2D ATRIBUTOS
	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	PORTAL_STATE _state = PORTAL_STATE::DESACTIVADO;
	float animationTimer = 0;
	bool touched = false;


public:

	Portal(sf::Vector2f newPosition, b2World& world, float pixelMetro);

	void setPositionBody(sf::Vector2f newPosition);

	void setBodyInWorld(b2World& world);

	void setSizeBody();


	void setFixture();

	b2Vec2 getPositionBody();

	void setTexture(std::string texture);

	void SetTextureRectAnimated();

	void setAnimationState();

	void animationControl(float deltaTime);

	void Update(int row, float deltaTime);

	void setTouched();

	bool isTouched();

	void destroyBody(b2World& world);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};