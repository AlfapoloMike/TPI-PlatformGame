#include "Map.h"

/// 1 = nivel 1
/// 0 = boss

Map::Map(int nivel) {

	_nivel = nivel;
	setAnimationState();
	_shape.setPosition(60.0f, -300.0f);


}



void Map::setTexture(std::string texture)
{
	_texture.loadFromFile(texture);
	_shape.setTexture(_texture);
}

void Map::SetTextureRectAnimated() {

	_shape.setTextureRect(_animation.uvRect);

}

void Map::setAnimationState()
{

		setTexture("./assets/map/MapHitted.png");
		_animation.setImageCount(sf::Vector2u(6, 1));
		_animation.setSwitchTime(0.12f);
		_animation.setImageUvRectSize(&_texture);

}

void Map::animationControl(float deltaTime) {

	if (_state == MAP_STATE::NORMAL) {
		animationTimer += deltaTime;
	
		if (animationTimer >= 2.0f && _nivel == 0) {
			_state = MAP_STATE::DISTORTION;
			animationTimer = 0;
		}
	}
	else if (_state == MAP_STATE::DISTORTION) {
		animationTimer += deltaTime;
		if (animationTimer >= 0.6f) {
			animationTimer = 0;
			_state = MAP_STATE::NORMAL;

		}
	}

}

void Map::update(int row, float deltaTime) {

	animationControl(deltaTime);
	_shape.setTextureRect(_animation.uvRect);
	if (_state == MAP_STATE::NORMAL) {
		_animation.Update(row, deltaTime, 1);

	}
	else if (_state == MAP_STATE::DISTORTION) {

		_animation.Update(row, deltaTime);

	}
}
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape, states);
}

sf::Sprite Map::getShape() {
	return _shape;
}
