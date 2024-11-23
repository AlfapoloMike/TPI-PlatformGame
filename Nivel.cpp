#include "Nivel.h"
#include <algorithm>


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
	setPlayerView();
	setUI();
}

void Nivel::setPlayer(b2World& world) {
	_personaje = new Jugador(world);

	if (_personaje == nullptr) {
		return;
	}
}
void Nivel::setPlayerView() {
	b2Vec2 position = _personaje->getPosition();
	_vista.setCenter(position.x * 40, 600 - position.y * 40);
	_vistaSize.x = _vista.getSize().x / 2;
	_vistaSize.y = _vista.getSize().y / 2;
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
		enemigos.push_back(std::make_shared<Conejo>(sf::Vector2f(18.0f, 8.0f), sf::Vector2f(0.425f, 0.55f), world, sf::Vector2f(0.2f, 1.1f), pixelMetro));
		enemigos.push_back(std::make_shared<Conejo>(sf::Vector2f(24.0f, 4.0f), sf::Vector2f(0.425f, 0.55f), world, sf::Vector2f(0.2f, 1.1f), pixelMetro));
		enemigos.push_back(std::make_shared<Conejo>(sf::Vector2f(30.0f, 11.0f), sf::Vector2f(0.425f, 0.55f), world, sf::Vector2f(0.2f, 1.1f), pixelMetro));
		enemigos.push_back(std::make_shared<Conejo>(sf::Vector2f(28.0f, 20.0f), sf::Vector2f(0.425f, 0.55f), world, sf::Vector2f(0.2f, 1.1f), pixelMetro));


		break;
		
	default:
		break;
		
	}

}

void Nivel::setFruits(b2World& world, float deltaTime)
{
	if (_frutas.size() < 16) {

		_fruitSpawnerTime += deltaTime;
		if (_fruitSpawnerTime > 1.0f) {

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

		_mapa= new Map(1);
		if (_mapa == nullptr) {
			return;
		}

		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(2.5f, 10.37f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(18.25f, 2.85f), sf::Vector2f(16.75f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(14.25f, 4.85f), sf::Vector2f(5.75f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(11.25f, 8.85f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(16.5f, 7.85f), sf::Vector2f(2.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(9.75f, 11.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(5.25f, 12.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(17.5f, 10.85f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(23.25f, 6.85f), sf::Vector2f(1.75f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(25.0f, 4.35f), sf::Vector2f(2.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(20.75f, 10.35f), sf::Vector2f(0.6f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(28.25f, 7.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(30.75f, 9.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(33.25f, 11.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(30.25f, 13.85f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(26.25f, 15.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(31.25f, 16.85f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(26.25f, 19.85f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(31.25f, 19.85f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(33.75f, 6.85f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(20.75f, 17.35f), sf::Vector2f(1.75f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(6.25f, 17.85f), sf::Vector2f(9.75f, 0.1f), world, true));




		////OBSTACULO
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(20.75f, 6.5f), sf::Vector2f(0.5f, 3.75f), world, false));


		///// BORDES DEL MAPA
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(1.25f, 12.0f), sf::Vector2f(0.1f, 10.5f), world, false));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(35.25f, 12.0f), sf::Vector2f(0.1f, 10.5f), world, false));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(18.25f, 1.375), sf::Vector2f(16.75f, 0.1f), world, false));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(18.25f, 22.75f), sf::Vector2f(16.75f, 0.1f), world, false));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(8.75f, 17.0f), sf::Vector2f(7.15f, 0.85f), world, false));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(1.55f, 20.75f), sf::Vector2f(0.25f, 4.25f), world, false));

		break;
	case NIVEL_2:
		break;
	case NIVEL_3:
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

		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(18.0f, 12.0f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(12.75f, 12.5f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(8.75f, 8.5f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Fatbird>(sf::Vector2f(7.50f, 20.0f), sf::Vector2f(0.5f, 0.6f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		///8.50f, 19.0f

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
		if (auto fatbird = std::dynamic_pointer_cast<Fatbird>(aldeano)) {
			fatbird->updateVillager(0, deltaTime);
		}
	}
	
	_background.backgroundUpdate();
	
	_personaje->update(0, deltaTime);


	_ui.update(deltaTime,_personaje->getVida());


	sf::Vector2f position = sf::Vector2f(_personaje->getPosition().x, _personaje->getPosition().y);

	position.x = std::clamp(position.x*40, _vistaSize.x, _nivelSize.x - _vistaSize.x);
	position.y = std::clamp(position.y*40, _vistaSize.y, _nivelSize.y - _vistaSize.y);



	_vista.setCenter(position.x, 600 - position.y);	


	gameStateController();

}

void Nivel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}



void Nivel::nivelDrawer(sf::RenderWindow& window)
{
	window.setView(_vista);


	window.draw(_background);

	window.draw(_mapa->getShape());

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
		if (auto fatbird = std::dynamic_pointer_cast<Fatbird>(aldeano)) {
			window.draw(fatbird->getSprite());
		}
	}


	for (int i = 0; i < _frutas.size(); i++) {
		window.draw(*_frutas[i]);
	}

	window.draw(*_personaje);


	window.setView(window.getDefaultView());

	_ui.drawUi(window);

}

void Nivel::enemiesCreator() {

}

void Nivel::setUI() {


}

void Nivel::gameStateController()
{
	bool* _alive = _personaje->getVida();
	int time = _ui.getTime();
	if (_alive[0] == false || time >=3) {
		std::cout << " LA PARTIDA HA TERMINADO - PERDISTE ! " << std::endl;
	}
}

Nivel::~Nivel()
{

	if (_personaje != nullptr) {
		delete _personaje;
	}
	if (_mapa != nullptr) {
		delete _mapa;
	}

}

void checkFruits() {

}

Plataformas Nivel::getPlataforma(int plataforma)
{
	return _plataformas[plataforma];
}



