#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Laser.h"
#include "IceBall.h"

enum class CRYSTAL_TYPE {
	LASER,
	ICEBALL,
};

class Crystal : public sf::Drawable {
protected:

	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::Vector2f _size;
	Animation _animation;
	Laser* _laser;

	float spawnTime=0;
	std::vector<std::unique_ptr<IceBall>> _iceBall;
	CRYSTAL_TYPE _type;


	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	b2Vec2 _positionBody;
	sf::Vector2f _velocidad = sf::Vector2f(2.5f, 2.5f);

public:

	Crystal(sf::Vector2f newPosition, b2World& world, int pixelMetro, int type, bool laserR);

	void setType(int type);

	void setPositionBody(sf::Vector2f newPosition);

	void setRandomPosition();

	void setBodyInWorld(b2World& world);

	void setSizeBody();

	void setFixture();

	b2Vec2 getPositionBody();

	void setTexture(std::string texture);

	void SetTextureRectAnimated();

	void setAnimationState();

	void Update(int row, float deltaTime, b2World& world);


	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void move();

	void changeDirection();

	void spawnIceBall(b2World& world, float deltaTime);

	bool isLaser();

	~Crystal();
};