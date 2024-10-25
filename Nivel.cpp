#include "Nivel.h"

Nivel::Nivel(int level)
{


	switch (level)
	{
	case 0:
		_nivel = NIVELES::MENU;
		break;
	case 1:
		_nivel = NIVELES::NIVEL_1;
		//setEnemigos(level);
		break;
	case 2:
		_nivel = NIVELES::NIVEL_2;
		break;
	case 3:
		_nivel = NIVELES::NIVEL_3;
		break;
	default:
		break;
	}

	setMap();
	setEnemigos();
}


void Nivel::setEnemigos()
{
	switch (_nivel)
	{
	case NIVEL_1:

		_enemigos = new Enemigo * [3];

		if (_enemigos == nullptr) {
			std::cout << "No se asigno memoria";
			return;
		}
		
		_enemigos[0] = new Skull(sf::Vector2f(550.0f, 350.0f), sf::Vector2f(2.f, 2.f));
		_enemigos[1] = new Skull(sf::Vector2f(350.0f, 250.0f), sf::Vector2f(2.f, 2.f));
		_enemigos[2] = new Skull(sf::Vector2f(620.0f, 180.0f), sf::Vector2f(2.f, 2.f));

		break;
		
	default:
		break;
		
	}

}

void Nivel::setMap()
{
	switch (_nivel)
	{
	case NIVEL_1:
		_mapa = Map::Map(1);
		_plataformas = new Plataformas[10];
		mappingPlatform(_plataformas, 1);
		break;
	case NIVEL_2:
		//_mapa = Map::Map(2);
		break;
	case NIVEL_3:
		//_mapa = Map::Map(2);
		break;
	case MENU:
		break;
	default:
		break;
	}
}



void Nivel::nivelUpdate(sf::RenderWindow& window, float deltaTime)
{
	
	
	for (int i = 0; i < 3; i++) {

		_enemigos[i]->updateEnemie(0, deltaTime);
	}
	
	_background.backgroundUpdate();
	


}

void Nivel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}


void Nivel::nivelDrawer(sf::RenderWindow& window)
{
	window.draw(_background);

	_mapa.mapDrawer(window);
	

	for (int i = 0; i < 3; i++) {
		window.draw(_enemigos[i]->getSprite());
	}

	for (int i = 0; i < 10; i++) {
		window.draw(_plataformas[i]);
	}
}

void Nivel::enemiesCreator() {

}

Nivel::~Nivel()
{
	if (_plataformas != nullptr) {
		delete[] _plataformas;
	}
	for (int i = 0; i < 3; ++i) {
		delete _enemigos[i];  // Libera cada enemigo
	}
	delete[] _enemigos;
}

