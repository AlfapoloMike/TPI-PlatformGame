#include "Map.h"


Map::Map(int nivel) {

	_nivel = nivel;

	_texture.loadFromFile("./assets/map/Map.png");
	_shape.setTexture(_texture);
	_shape.setPosition(60.0f, -300.0f);


}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape, states);
}

sf::Sprite Map::getShape() {
	return _shape;
}
