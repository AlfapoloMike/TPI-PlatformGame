#pragma once

#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "CollisionCategories.h"


enum class ICEBALL_STATE {
	FLOATING,
	ACTIVADO,
	DESACTIVADO,
};

class IceBall : public sf::Drawable {
protected:

	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::Vector2f _size;
	Animation _animation;
	ICEBALL_STATE _state = ICEBALL_STATE::FLOATING;
	float timer = 0;
	///TEST DE TAMANIO
	//sf::RectangleShape _colisionSquare
	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	b2Vec2 _positionBody;
	sf::Vector2f _velocidad = sf::Vector2f(1.0f, 1.0f);
	bool destroyed = false;

public:

	IceBall(sf::Vector2f newPosition, int pixelMetro, b2World& world);

	void setPositionBody(sf::Vector2f newPosition);

	void setBodyInWorld(b2World& world);

	void setSizeBody();

	void setFixture();

	b2Vec2 getPositionBody();

	void checkBody(b2World& world);

	void AnimationControl(float deltaTime);

	void setRandomDirection();

	void setNewDirection(bool horizontalSide, bool verticalSide);

	void move();

	void setSpritePosition(sf::Vector2f newPosition);

	void setTexture(std::string texture);

	void SetTextureRectAnimated();

	void setAnimationState();

	void Update(int row, float deltaTime, sf::Vector2f newPosition, b2World& world);



	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void explodeBall();

	bool Destroyed();

	sf::Sprite getShape();

};