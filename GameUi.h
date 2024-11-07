#pragma once
#include "Corazon.h"


class GameUi {
private:
	sf::Font _font;

	Corazon _corazones[4]{
	Corazon::Corazon(sf::Vector2f(90.0f,25.0f)),
	Corazon::Corazon(sf::Vector2f(130.0f,25.0f)),
	Corazon::Corazon(sf::Vector2f(170.0f,25.0f)),
	Corazon::Corazon(sf::Vector2f(210.0f,25.0f))
	};

	sf::Text _timer;
	sf::Text _points;
	int _timeCount[2]{};
	sf::Clock _reloj;


public:
	GameUi();
	void setFont();
	void setCorazones();
	void setTimer();
	void setPoints();
	void update(float deltaTime);
	void drawUi(sf::RenderWindow& window);
	~GameUi();
};