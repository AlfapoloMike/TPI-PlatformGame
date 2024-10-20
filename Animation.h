#pragma once
#include <SFML\Graphics.hpp>

class Animation
{

public:
	Animation(sf::Texture* texture, sf::Vector2u imageCountNew, float switchTime);
	Animation();

	void setImageCount(sf::Vector2u imageCountNew);
	void setSwitchTime(float switchTimeNew);
	void setImageUvRectSize(sf::Texture* image);
	
	~Animation();
	sf::IntRect getUvRect();
	void Update(int row, float deltaTime);

public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;


};

