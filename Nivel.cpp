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
	setPlayer(world);
	setVillager(world, pixelMetro);
	setUI();
}

void Nivel::setPlayer(b2World& world) {
	_personaje = new Jugador(world);

	if (_personaje == nullptr) {
		return;
	}
}

void Nivel::setEnemigos(b2World& world, float pixelMetro)
{
	switch (_nivel)
	{
	case NIVEL_1:
	
		enemigos.push_back(std::make_shared<Skull>(sf::Vector2f(7.75f, 10.5f), sf::Vector2f(0.34f, 0.3f), world, sf::Vector2f(1.5f, 1.5f), pixelMetro));
		enemigos.push_back(std::make_shared<Skull>(sf::Vector2f(10.75f, 5.5f), sf::Vector2f(0.34f, 0.3f), world, sf::Vector2f(1.5f, 1.5f), pixelMetro));
		enemigos.push_back(std::make_shared<Skull>(sf::Vector2f(13.75f, 7.5f), sf::Vector2f(0.34f, 0.3f), world, sf::Vector2f(1.5f, 1.5f), pixelMetro));
		enemigos.push_back(std::make_shared<Conejo>(sf::Vector2f(8.0f, 4.0f), sf::Vector2f(0.425f, 0.55f), world, sf::Vector2f(0.2f, 1.1f), pixelMetro));
		enemigos.push_back(std::make_shared<Conejo>(sf::Vector2f(12.0f, 8.0f), sf::Vector2f(0.425f, 0.55f), world, sf::Vector2f(0.2f, 1.1f), pixelMetro));

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

	for (int i = 0; i < _frutas.size(); i++) {
		if (_frutas[i]->getPickedState() == true) {
			std::cout << _frutas[i]->getPoints() << std::endl;
			_ui.sumarPuntos(_frutas[i]->getPoints());
			_frutas.erase(_frutas.begin() + i);
			i--;
		}
	}

}

void Nivel::setMap(b2World& world)
{
	switch (_nivel)
	{
	case NIVEL_1:
		_mapa = Map::Map(1);

		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(2.5f, 10.37f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(10.0f, 2.85f), sf::Vector2f(8.5f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(13.5f, 4.85f), sf::Vector2f(5.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(11.25f, 8.85f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(16.5f, 7.85f), sf::Vector2f(2.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(7.0f, 9.35f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(5.0f, 10.85f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(14.0f, 11.37f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(17.5f, 10.37f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(1.37f, 7.5f), sf::Vector2f(0.1f, 6.0f), world, false));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(18.625f, 7.5f), sf::Vector2f(0.1f, 6.0f), world, false));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(10.0f, 1.375), sf::Vector2f(9.0f, 0.1f), world, false));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(10.0f, 13.675f), sf::Vector2f(9.0f, 0.1f), world, false));

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

void Nivel::setVillager(b2World& world, float pixelMetro) {
	switch (_nivel)
	{
	case NIVEL_1:

		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(3.75f, 11.5f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(12.75f, 12.5f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(8.75f, 8.5f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));

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

	for (const auto& enemigo : enemigos) {
		if (auto calavera = std::dynamic_pointer_cast<Skull>(enemigo)) {
			calavera->updateEnemie(0, deltaTime);
		}
		else if (auto conejo = std::dynamic_pointer_cast<Conejo>(enemigo)) {
			conejo->updateEnemie(0, deltaTime);
		}
	}
	
	for (const auto& aldeano : aldeanos) {
		if (auto tortuga = std::dynamic_pointer_cast<Tortuga>(aldeano)) {
			tortuga->updateVillager(0, deltaTime);
		}
	}
	
	_background.backgroundUpdate();
	
	_personaje->update(0, deltaTime);



	_ui.update(deltaTime,_personaje->getVida());


}

void Nivel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}



void Nivel::nivelDrawer(sf::RenderWindow& window)
{
	window.draw(_background);

	_mapa.mapDrawer(window);
	

	for (int i = 0; i < _plataformasN.size(); i++) {
		window.draw(_plataformasN[i]->getShape());
	}

	for (const auto& enemigo : enemigos) {
		if (auto calavera = std::dynamic_pointer_cast<Skull>(enemigo)) {
			window.draw(calavera->getSprite());
		}
		else if (auto conejo = std::dynamic_pointer_cast<Conejo>(enemigo)) {
			window.draw(conejo->getSprite());
		}
	}

	for (const auto& aldeano : aldeanos) {
		if (auto tortuga = std::dynamic_pointer_cast<Tortuga>(aldeano)) {
			window.draw(tortuga->getSprite());
		}
	}


	for (int i = 0; i < _frutas.size(); i++) {
		window.draw(*_frutas[i]);
	}

	window.draw(*_personaje);

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

	if (_personaje != nullptr) {
		delete _personaje;
	}

}

void checkFruits() {

}

Plataformas Nivel::getPlataforma(int plataforma)
{
	return _plataformas[plataforma];
}



