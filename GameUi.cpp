#include "GameUi.h"

GameUi::GameUi()
{
	setGameUiBackground();
	setFont();
	setTimer();
	setPoints();
}

void GameUi::setFont()
{
	//_font.loadFromFile("./assets/fonts/Pixel_Times.ttf");
	_font.loadFromFile("./assets/fonts/Pixelon.ttf");
}

void GameUi::setCorazones(bool vidas[4])
{
	for (int i = 0; i < 4; i++) {
		if (vidas[i] == false) {
			_corazones[i].setActive(false);
		}
	}
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
	_points.setFont(_font);
	_points.setString("Puntos: "+ std::to_string(_totalPoints));
	_points.setCharacterSize(24);
	_points.setFillColor(sf::Color::White);
	_points.setPosition(400, 10);
}
void GameUi::sumarPuntos(int puntos)
{
	_totalPoints += puntos;
}
void GameUi::setGameUiBackground()
{

	_texture.loadFromFile("./assets/map/Borde.png");
	_shape.setTexture(_texture);

}
int GameUi::getTime()
{
	return _timeCount[0];
}
void GameUi::update(float deltaTime, bool vidas[4])
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

	_points.setString("Puntos: " + std::to_string(_totalPoints));


	setCorazones(vidas);

	for (int i = 0; i < 4; i++) {
		_corazones[i].update(deltaTime);
	}
}
void GameUi::drawUi(sf::RenderWindow& window)
{
	window.draw(_shape);
	window.draw(_timer);
	window.draw(_points);
	for (int i = 0; i < 4; i++) {
		window.draw(_corazones[i]);
	}
}


GameUi::~GameUi()
{
}
