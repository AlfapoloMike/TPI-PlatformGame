#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"

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
public:
	Portal(sf::Vector2f newPosition);

	void setTexture(std::string texture);

	void SetTextureRectAnimated();

	void setAnimationState();

	void Update(int row, float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};