#include "GameUi.h"

GameUi::GameUi()
{
	setFont();
	setTimer();
	setPoints();
}

void GameUi::setFont()
{
	_font.loadFromFile("./assets/fonts/Pixel_Times.ttf");
}

void GameUi::setCorazones()
{
}

void GameUi::setTimer()
{
	_timer.setFont(_font);
	_timer.setString("0:00");
	_timer.setCharacterSize(24);
	_timer.setFillColor(sf::Color::White);
	_timer.setPosition(300, 10);
}

void GameUi::setPoints()
{
	int puntaje = 3500;
	_points.setFont(_font);
	_points.setString("Puntos: "+ std::to_string(puntaje));
	_points.setCharacterSize(24);
	_points.setFillColor(sf::Color::White);
	_points.setPosition(400, 10);
}
void GameUi::update(float deltaTime)
{

	///// AQUI SE TENDRIA QUE ESTAR RECIBIENDO LA VIDA DEL JUGADOR COMO PARAMETRO PARA MODIFICAR LOS CORAZONES.

	if (_reloj.getElapsedTime().asSeconds() >= 1.0f) {

		_timeCount[1]++;
		_reloj.restart();
		if (_timeCount[1] < 10) {
			_timer.setString(std::to_string(_timeCount[0]) + ":0" + std::to_string(_timeCount[1]));
		}
		else if (_timeCount[1] > 9 && _timeCount[1]< 60) {
			_timer.setString(std::to_string(_timeCount[0]) + ":" + std::to_string(_timeCount[1]));
		}
		else if (_timeCount[1] == 60) {
			_timeCount[1] = 0;
			_timeCount[0]++;
			_timer.setString(std::to_string(_timeCount[0]) + ":0" + std::to_string(_timeCount[1]));
		}
		
	}

	for (int i = 0; i < 4; i++) {
		_corazones[i].update(deltaTime);
	}
}
void GameUi::drawUi(sf::RenderWindow& window)
{
	window.draw(_timer);
	window.draw(_points);
	for (int i = 0; i < 4; i++) {
		window.draw(_corazones[i]);
	}
}


GameUi::~GameUi()
{
}
