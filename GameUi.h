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
	int _totalPoints = 0;
	int _timeCount[2]{};
	sf::Clock _reloj;
	sf::Sprite _shape;
	sf::Texture _texture;


public:
	GameUi();
	void setFont();
	void setCorazones(bool vidas[4]);
	void setTimer();
	void setPoints();
	void sumarPuntos(int puntos);
	void setGameUiBackground();
	int getTime();
	int getPoints();
	void update(float deltaTime, bool vidas[4]);
	void drawUi(sf::RenderWindow& window);
	~GameUi();
};