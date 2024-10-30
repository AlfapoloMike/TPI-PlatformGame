#pragma once
#include "Corazon.h"


class GameUi {
private:
	sf::Font _font;
	Corazon _corazones;
	sf::Text _timer;
	sf::Text _points;
	int _timeCount[2]{};
	sf::Clock _reloj;
	/////CajaTexto _puntos;

public:
	GameUi();
	void setFont();
	void setCorazones();
	void setTimer();
	void setPoints();
	void update();
	void drawUi(sf::RenderWindow& window);
	~GameUi();
};