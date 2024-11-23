#include "Background.h"


backgroundTile::backgroundTile() {
	_texture.loadFromFile("./assets/map/Purple.png");
	_texture.setRepeated(true);
	_sprite.setTextureRect(sf::IntRect(0, 0, 1400, 900));
	_sprite.setTexture(_texture);
}
void backgroundTile::backgroundUpdate() {
	_sprite.move(0, +1);
	if (_sprite.getPosition().y > -308) {
		_sprite.setPosition(sf::Vector2f(0.0f, -372.0f));
	}
}

void backgroundTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
