#include "Animation.h"


Animation::Animation(sf::Texture* texture, sf::Vector2u imageCountNew, float switchTime) {

	this->imageCount = imageCountNew;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

}
Animation::Animation() {

}
/*
void Animation::setImageCount(sf::Vector2u imageCountNew) {
	imageCount = imageCountNew;
}
void Animation::setImageUvRectSize(sf::Texture *image) {
	currentImage = image;
}
void Animation::setSwitchTime(float switchTimeNew) {
	switchTime = switchTimeNew;
}
*/


Animation::~Animation() {

}

sf::IntRect Animation::getUvRect()
{
	return uvRect;
}

void Animation::Update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {

			currentImage.x = 0;
		}

	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;


}
