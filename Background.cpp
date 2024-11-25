#include "Background.h"


backgroundTile::backgroundTile() {
	setRandomType();
	setTextureType();
}
void backgroundTile::backgroundUpdate(float deltaTime, bool change) {

	if (change == true) {
		if (_change == false) {
			setRandomType();
			setTextureType();
			_change = true;
		}
	}

	if (_change == true) {
		counterTime += deltaTime;
		if (counterTime > 1.3f) {
			counterTime = 0;
			_change = false;
		}
	}

	_sprite.move(0, +1);
	if (_sprite.getPosition().y > -308) {
		_sprite.setPosition(sf::Vector2f(0.0f, -372.0f));
	}
}

void backgroundTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void backgroundTile::setRandomType() {


	int max = 7, min = 1;
	int pre_type = (float)(rand() % (max - min + 1) + min);
	if (pre_type == _type) {
		setRandomType();
	}
	else {
		_type = pre_type;
	}
}

void backgroundTile::setTextureType() {

	if (_type == 1) {
		_texture.loadFromFile("./assets/map/Green.png");
		_texture.setRepeated(true);
		_sprite.setTextureRect(sf::IntRect(0, 0, 1400, 900));
		_sprite.setTexture(_texture);
	}
	else if (_type == 2) {
		_texture.loadFromFile("./assets/map/Blue.png");
		_texture.setRepeated(true);
		_sprite.setTextureRect(sf::IntRect(0, 0, 1400, 900));
		_sprite.setTexture(_texture);
	}
	else if (_type == 3) {
		_texture.loadFromFile("./assets/map/Brown.png");
		_texture.setRepeated(true);
		_sprite.setTextureRect(sf::IntRect(0, 0, 1400, 900));
		_sprite.setTexture(_texture);
	}
	else if (_type == 4) {
		_texture.loadFromFile("./assets/map/Gray.png");
		_texture.setRepeated(true);
		_sprite.setTextureRect(sf::IntRect(0, 0, 1400, 900));
		_sprite.setTexture(_texture);
	}
	else if (_type == 5) {
		_texture.loadFromFile("./assets/map/Pink.png");
		_texture.setRepeated(true);
		_sprite.setTextureRect(sf::IntRect(0, 0, 1400, 900));
		_sprite.setTexture(_texture);
	}
	else if (_type == 6) {
		_texture.loadFromFile("./assets/map/Purple.png");
		_texture.setRepeated(true);
		_sprite.setTextureRect(sf::IntRect(0, 0, 1400, 900));
		_sprite.setTexture(_texture);
	}
	else if (_type == 7) {
		_texture.loadFromFile("./assets/map/Yellow.png");
		_texture.setRepeated(true);
		_sprite.setTextureRect(sf::IntRect(0, 0, 1400, 900));
		_sprite.setTexture(_texture);
	}

}