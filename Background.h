#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

class backgroundTile : public sf::Drawable
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f velocity;
	int _type = 0;
	int _change = false;
	float counterTime = 0;
public:
	backgroundTile();
	void backgroundUpdate(float deltaTime, bool change);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	void setRandomType();

	void setTextureType();

};

