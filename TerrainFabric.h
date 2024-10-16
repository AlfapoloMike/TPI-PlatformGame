#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class backgroundAnimation
{
private:
	sf::VertexArray array[360]{};
	sf::Texture _texture;
	float _sizeX = 40.0f;
	float _sizeY = 40.0f;
	float _velocity = 0.5f;

public:
	backgroundAnimation();
	void backgroundUpdate();
	void setPositionBackground();

};

class backgroundTile : public sf::Drawable
{
	private:
		sf::Sprite _sprite;
		sf::Texture _texture;
		sf::Vector2f velocity;
	public:
		backgroundTile() {
			_texture.loadFromFile("Brown.png");
			_texture.setRepeated(true);
			_sprite.setTextureRect(sf::IntRect(0, 0, 800.0f, 576.0f));
			_sprite.setTexture(_texture);
		}
		void backgroundUpdate() {
			_sprite.move(0, +1);
			if (_sprite.getPosition().y > 32) {
				_sprite.setPosition(sf::Vector2f(0.0f, -32.0f));
			}
		}
		void draw(sf::RenderTarget& target, sf::RenderStates states)const {
			target.draw(_sprite, states);
		}

		

};


