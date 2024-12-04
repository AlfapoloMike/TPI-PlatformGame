#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "CollisionCategories.h"

enum class LASER_STATE {
	DESACTIVADO,
	CARGANDO,
	ACTIVADO
};

class Laser : public sf::Drawable {
protected:

	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::Vector2f _size;
	Animation _animation;
	LASER_STATE _state = LASER_STATE::CARGANDO;
	float timer = 0;
	///TEST DE TAMANIO
	//sf::RectangleShape _colisionSquare
	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	b2Vec2 _positionBody;
	sf::Vector2f _velocidad = sf::Vector2f(2.0f, 2.0f);
	bool _sideR = false;

public:

	Laser(sf::Vector2f newPosition, int pixelMetro, bool sideR);

	void setPositionBody(sf::Vector2f newPosition);

	void setBodyInWorld(b2World& world);

	void setSizeBody();

	void setFixture();

	b2Vec2 getPositionBody();


	void createOrDestroyBody(sf::Vector2f newPosition, b2World& world);

	bool getSideR();

	void setSpritePosition(sf::Vector2f newPosition);

	void setTexture(std::string texture);

	void SetTextureRectAnimated();

	void setAnimationState();

	void AnimationControl(float deltaTime, sf::Vector2f newPosition, b2World& world);

	void Update(int row, float deltaTime, sf::Vector2f newPosition, b2World& world);



	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite getShape();

};