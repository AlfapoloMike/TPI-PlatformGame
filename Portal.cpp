#include "Portal.h"

Portal::Portal(sf::Vector2f newPosition)
{
	_sprite.setPosition(newPosition.x, newPosition.y);
	setAnimationState();
}

void Portal::setTexture(std::string texture)
{
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Portal::SetTextureRectAnimated() {

	_sprite.setTextureRect(_animation.uvRect);

}

void Portal::setAnimationState()
{

		setTexture("./assets/map/portalsSpriteSheet.png");
		_animation.setImageCount(sf::Vector2u(4, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);


}

void Portal::Update(int row, float deltaTime) {

	_sprite.setTextureRect(_animation.uvRect);
	_animation.Update(row, deltaTime);

}



void Portal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}