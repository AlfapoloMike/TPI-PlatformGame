#include "Nivel.h"

Nivel::Nivel(int level, b2World& world, float pixelMetro)
{
	_pixelMetro = pixelMetro;

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

	setMap(world);
	setEnemigos(world, pixelMetro);
	setUI();
}


void Nivel::setEnemigos(b2World& world, float pixelMetro)
{
	switch (_nivel)
	{
	case NIVEL_1:

		_enemigos = new Enemigo * [4];

		if (_enemigos == nullptr) {
			std::cout << "No se asigno memoria";
			return;
		}
		
		_enemigos[0] = new Skull(sf::Vector2f(550.0f, 500.0f), sf::Vector2f(2.f, 2.f),1.0f);
		_enemigos[1] = new Skull(sf::Vector2f(350.0f, 250.0f), sf::Vector2f(2.f, 2.f), 40.0f);
		_enemigos[2] = new Skull(sf::Vector2f(620.0f, 180.0f), sf::Vector2f(2.f, 2.f), 40.0f);
		_enemigos[3] = new Conejo(sf::Vector2f(9.0f, 13.0f), sf::Vector2f(0.5f, 0.5f), world, sf::Vector2f(0.85f, 1.1f), 2.0f, 15.0f, 40);

		break;
		
	default:
		break;
		
	}

}

void Nivel::setFruits(b2World& world, float deltaTime)
{
	if (_frutas.size() < 8) {

		_fruitSpawnerTime += deltaTime;
		if (_fruitSpawnerTime > 4.0f) {

			_frutas.push_back(std::make_unique<Frutas>(world));

			_fruitSpawnerTime = 0;

		}
	}

}

void Nivel::setMap(b2World& world)
{
	switch (_nivel)
	{
	case NIVEL_1:
		_mapa = Map::Map(1);
		_plataformas = new Plataformas[10];
		mappingPlatform(_plataformas, 1, world, _pixelMetro);
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



void Nivel::nivelUpdate(b2World& world, sf::RenderWindow& window, float deltaTime)
{
	
	setFruits(world, deltaTime);

	for (int i = 0; i < _frutas.size(); i++) {
		_frutas[i]->fruitUpdate(0, deltaTime);
	}
	
	for (int i = 0; i < 4; i++) {

		_enemigos[i]->updateEnemie(0, deltaTime);
	}
	
	
	_background.backgroundUpdate();
	
	_ui.update(deltaTime);


}

void Nivel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}


void Nivel::nivelDrawer(sf::RenderWindow& window)
{
	window.draw(_background);

	_mapa.mapDrawer(window);
	
	//COMENTAR ESTO >>
	for (int i = 0; i < 4; i++) {
		window.draw(_enemigos[i]->getSprite());
	}
	

	for (int i = 0; i < 10; i++) {
		window.draw(_plataformas[i]);
	}


	for (int i = 0; i < _frutas.size(); i++) {
		window.draw(*_frutas[i]);
	}

	_ui.drawUi(window);

}

void Nivel::enemiesCreator() {

}

void Nivel::setUI() {


}

void Nivel::gameStateController()
{

}

Nivel::~Nivel()
{
	if (_plataformas != nullptr) {
		delete[] _plataformas;
	}
	if (_enemigos != nullptr) {
		
		for (int i = 0; i < 4; ++i) {
			if (_enemigos[i] != nullptr) {
				delete _enemigos[i];  // Libera cada enemigo

			}
		}
		
		delete[] _enemigos;
	}


}
/*
sf::Sprite Nivel::getSpriteEnemigo(int enemigo){
	return _enemigos[enemigo]->getSprite();
}
*/

Plataformas Nivel::getPlataforma(int plataforma)
{
	return _plataformas[plataforma];
}



