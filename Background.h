#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class backgroundTile : public sf::Drawable
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f velocity;
public:
	backgroundTile();
	void backgroundUpdate();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;

};

