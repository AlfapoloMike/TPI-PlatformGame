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
	
	_overlay = sf::RectangleShape(sf::Vector2f(1460, 960));
	_overlay.setPosition(_overlay.getPosition().x, -360);
	_overlay.setFillColor(sf::Color(0, 0, 128, 100));
	

	setPortalAlert();

}

void Nivel::setPlayer(b2World& world) {
	_personaje = std::make_unique<Jugador>(world);

}
void Nivel::setMago(b2World& world) {
	mago = std::make_unique<Mage>(world, sf::Vector2f(5.0f, 18.8f), 40);

}
void Nivel::setPlayerView() {
	playerPosition = sf::Vector2f(_personaje->getPosition().x, _personaje->getPosition().y);
	_vista.setCenter(playerPosition.x * 40, 600 - playerPosition.y * 40);
	_vistaSize.x = _vista.getSize().x / 2;
	_vistaSize.y = _vista.getSize().y / 2;
}

void Nivel::setEnemigos(b2World& world, float pixelMetro)
{
	switch (_nivel)
	{
	case NIVELES::NIVEL_1:

		enemigos.push_back(std::make_shared<Skull>(sf::Vector2f(7.75f, 10.5f), sf::Vector2f(0.34f, 0.3f), world, sf::Vector2f(1.5f, 1.5f), pixelMetro));
		enemigos.push_back(std::make_shared<Skull>(sf::Vector2f(15.75f, 15.5f), sf::Vector2f(0.34f, 0.3f), world, sf::Vector2f(1.5f, 1.5f), pixelMetro));
		enemigos.push_back(std::make_shared<Skull>(sf::Vector2f(28.75f, 4.5f), sf::Vector2f(0.34f, 0.3f), world, sf::Vector2f(1.5f, 1.5f), pixelMetro));
		enemigos.push_back(std::make_shared<Conejo>(sf::Vector2f(18.0f, 8.0f), sf::Vector2f(0.425f, 0.55f), world, sf::Vector2f(0.2f, 1.1f), pixelMetro));
		enemigos.push_back(std::make_shared<Conejo>(sf::Vector2f(24.0f, 4.0f), sf::Vector2f(0.425f, 0.55f), world, sf::Vector2f(0.2f, 1.1f), pixelMetro));
		enemigos.push_back(std::make_shared<Conejo>(sf::Vector2f(30.0f, 11.0f), sf::Vector2f(0.425f, 0.55f), world, sf::Vector2f(0.2f, 1.1f), pixelMetro));
		

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

			frutasRecolectadas[_frutas[i]->getFruitType() - 1]++; // **************************
			_ui->sumarPuntos(_frutas[i]->getPoints());
			_frutas.erase(_frutas.begin() + i);
			i--;
		}
	}

}

void Nivel::setCrystals(b2World& world, float deltaTime) {

	_crystals.push_back(std::make_unique<Crystal>(sf::Vector2f(2.0f, 5.0f), world, 40, 2, false));
	_crystals.push_back(std::make_unique<Crystal>(sf::Vector2f(8.0f, 8.0f), world, 40, 1, false));
	_crystals.push_back(std::make_unique<Crystal>(sf::Vector2f(26.0f, 8.0f), world, 40, 1, false));
	_crystals.push_back(std::make_unique<Crystal>(sf::Vector2f(16.0f, 5.0f), world, 40, 1, false));
	_crystals.push_back(std::make_unique<Crystal>(sf::Vector2f(25.0f, 17.2f), world, 40, 1, false));
	_crystals.push_back(std::make_unique<Crystal>(sf::Vector2f(20.0f, 12.0f), world, 40, 1, false));
	_crystals.push_back(std::make_unique<Crystal>(sf::Vector2f(35.0f, 5.0f), world, 40, 2, true));


}

void Nivel::setTottems(b2World& world, float deltaTime) {

	if (_tottems.size() < 3) {
		_tottems.push_back(std::make_unique<Tottem>(world, 40));
	}

	for (int i = 0; i < _tottems.size(); i++) {
		if (_tottems[i]->isDestroyed() == true) {
			mago->damaged(_tottems[i]->isDestroyed());
			_tottems[i]->destroyBody(world);
			_tottems.erase(_tottems.begin() + i);
			i--;
		}
	}

}

void Nivel::setMap(b2World& world)
{
	switch (_nivel)
	{
	case NIVELES::NIVEL_1:

		_map = std::make_unique<Map>(1);

		_background = std::make_unique<backgroundTile>(false);

		_ui = std::make_unique<GameUi>();

		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(2.5f, 10.37f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(18.25f, 2.85f), sf::Vector2f(16.75f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(14.25f, 5.35f), sf::Vector2f(5.75f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(11.25f, 8.85f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(16.5f, 7.85f), sf::Vector2f(2.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(9.75f, 11.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(5.25f, 12.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(17.5f, 10.85f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(23.25f, 6.85f), sf::Vector2f(1.75f, 0.1f), world, true));

		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(29.0f, 5.35f), sf::Vector2f(2.0f, 0.1f), world, true));
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
	case NIVELES::BOSS:
		_map = std::make_unique<Map>(0);


		_background = std::make_unique<backgroundTile>(true);


		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(2.5f, 10.37f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(18.25f, 2.85f), sf::Vector2f(16.75f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(14.25f, 5.35f), sf::Vector2f(5.75f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(11.25f, 8.85f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(16.5f, 7.85f), sf::Vector2f(2.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(9.75f, 11.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(5.25f, 12.35f), sf::Vector2f(1.25f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(17.5f, 10.85f), sf::Vector2f(1.0f, 0.1f), world, true));
		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(23.25f, 6.85f), sf::Vector2f(1.75f, 0.1f), world, true));

		_plataformasN.push_back(std::make_unique<Plataformas>(sf::Vector2f(29.0f, 5.35f), sf::Vector2f(2.0f, 0.1f), world, true));
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
	case NIVELES::NIVEL_3:
		break;
	case NIVELES::MENU:
		break;
	default:
		break;
	}
}

void Nivel::setVillager(b2World& world, float pixelMetro) {
	switch (_nivel)
	{
	case NIVELES::NIVEL_1:

		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(18.0f, 12.0f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(28.0f, 7.0f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(6.0f, 20.0f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(12.75f, 12.5f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(3.75f, 8.5f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Tortuga>(sf::Vector2f(28.0f, 20.0f), sf::Vector2f(0.55f, 0.325f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Fatbird>(sf::Vector2f(23.5f, 15.0f), sf::Vector2f(0.5f, 0.6f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Fatbird>(sf::Vector2f(20.50f, 20.0f), sf::Vector2f(0.5f, 0.6f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Fatbird>(sf::Vector2f(3.50f, 8.0f), sf::Vector2f(0.5f, 0.6f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Rino>(sf::Vector2f(3.50f, 4.0f), sf::Vector2f(0.65f, 0.425f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		aldeanos.push_back(std::make_shared<Rino>(sf::Vector2f(24.50f, 4.0f), sf::Vector2f(0.65f, 0.425f), world, sf::Vector2f(1.5f, 0.0f), pixelMetro));
		///8.50f, 19.0f
		break;

	default:
		break;

	}

}

void Nivel::setPortal(b2World& world) {

	_portal = std::make_unique<Portal>(sf::Vector2f(8.0f, 20.0f), world, _pixelMetro);

}

void Nivel::nivelUpdate(b2World& world, sf::RenderWindow& window, float deltaTime)
{

	gameStateController(world);
	setMusic();  // ***********************************************************


	switch (_nivel)
	{
	case NIVELES::PRESET_NIVEL:
		_nivel = NIVELES::NIVEL_1;
		setMap(world);
		setEnemigos(world, _pixelMetro);
		setPlayer(world);
		setVillager(world, _pixelMetro);
		setPlayerView();
		for (int i = 0; i < 8; i++) { 
			frutasRecolectadas[i] = 0;
		}
		break;
	case NIVELES::NIVEL_1:

		/// <summary>
		/// ////// IMPLEMENTAR UN IF PARA PAUSAR <<<<<<<<<<<<<
		/// </summary>

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
			if (auto rino = std::dynamic_pointer_cast<Rino>(aldeano)) {
				rino->updateVillager(0, deltaTime);
			}
		}

		//// EFECTO CAMBIO DE FONDO ----
		_background->backgroundUpdate(deltaTime, _personaje->getIsHitted());
		//// EFECTO CAMBIO DE FONDO ----

		_map->update(0, deltaTime);

		_personaje->update(0, deltaTime);

		if (_portalState == true) {
			_portal->Update(0, deltaTime);
			_teleporting = _portal->isTouched();
		}


		_ui->update(deltaTime, _personaje->getVida());


		playerPosition = sf::Vector2f(_personaje->getPosition().x, _personaje->getPosition().y);

		playerPosition.x = std::clamp(playerPosition.x * 40, _vistaSize.x, _nivelSize.x - _vistaSize.x);
		playerPosition.y = std::clamp(playerPosition.y * 40, _vistaSize.y, _nivelSize.y - _vistaSize.y);



		_vista.setCenter(playerPosition.x, 600 - playerPosition.y);

		break;
	case NIVELES::PRESET_BOSS:

		_musicaFondo.stop(); // ************************************************************** PODRIA IR EN BOSS TAMBIEN
		_nivel = NIVELES::BOSS;
		setMap(world);
		setCrystals(world, 0);
		setMago(world);
		break;
	case NIVELES::MENU:


		if (menuSi) {
			menu.update(window, menuSi);

		}
		else {
			setLevel(NIVELES::PRESET_NIVEL);

		}

		break;
	case NIVELES::BOSS:

		_background->backgroundUpdate(deltaTime, _personaje->getIsHitted());


		setTottems(world, deltaTime);

		for (int i = 0; i < _crystals.size(); i++) {
			_crystals[i]->Update(0, deltaTime, world);
		}

		for (int i = 0; i < _tottems.size(); i++) {
			_tottems[i]->Update(0, deltaTime, world);
		}

		_map->update(0, deltaTime);


		_personaje->update(0, deltaTime);


		mago->Update(0, deltaTime, world);

		_ui->update(deltaTime, _personaje->getVida());


		playerPosition = sf::Vector2f(_personaje->getPosition().x, _personaje->getPosition().y);

		playerPosition.x = std::clamp(playerPosition.x * 40, _vistaSize.x, _nivelSize.x - _vistaSize.x);
		playerPosition.y = std::clamp(playerPosition.y * 40, _vistaSize.y, _nivelSize.y - _vistaSize.y);



		_vista.setCenter(playerPosition.x, 600 - playerPosition.y);

		break;
	case NIVELES::WIN:

		menu.setResultado(true);
		menu.update(window, menuSi);

		break;
	case NIVELES::LOSE:
		menu.setResultado(false);
		menu.update(window, menuSi);
		break;
	default:
		break;

	}
}

void Nivel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void Nivel::setLevel(NIVELES nivel) {
	_nivel = nivel;
}

void Nivel::cmdNivel(sf::Event& event) {
	switch (_nivel) {
	case NIVELES::MENU:

		//if (menuSi) {
			menu.manejoEvents(event, menuSi);
		//}
		break;
	case NIVELES::WIN:  // ******************************************* WIN LOSE cmdNIVEL ************************************************

		if (event.type == sf::Event::KeyPressed) { // *****************************
			if (event.key.code == sf::Keyboard::Escape) {
			//	std::cout << "APRETE ESCAPE EN WIN. Bloque para guardar puntaje y actualizar archivo" << std::endl;
				menu.setState("menu");
				PuntajeJugador jugador(menu.getNombreJugador(), menu.getPuntajeFinal());
				archivo.grabarMarcador(jugador);
				archivo.ordenarRanking();
				menu.resetAll();
				_nivel = NIVELES::MENU;
				menuSi = true;
			}
		}

		break;
	case NIVELES::LOSE:

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
			//	std::cout << "APRETE ESCAPE. Bloque para guardar puntaje y actualizar archivo" << std::endl;
				menu.setState("menu");
				PuntajeJugador jugador(menu.getNombreJugador(), menu.getPuntajeFinal());
				archivo.grabarMarcador(jugador);
				archivo.ordenarRanking();
				menu.resetAll();
				_nivel = NIVELES::MENU;
				menuSi = true;
			}
		}

		break;
	}
}

void Nivel::setMusic(){ // ******************************
	std::string rutaMusica;

	if (_musicaFondo.getStatus() != sf::Music::Playing) {
		switch (_nivel) {
		case NIVELES::PRESET_NIVEL:
			rutaMusica = "./assets/audios/nivel2.mp3"; // Hay audios opcionales para nivel en assets/audios
			_musicaFondo.setVolume(100);
			break;
		case NIVELES::BOSS:
			rutaMusica = "./assets/audios/hechicero.mp3";
			_musicaFondo.setVolume(100);
			break;
		}

		if (_nivel == NIVELES::PRESET_NIVEL || _nivel == NIVELES::BOSS) {
			if (!_musicaFondo.openFromFile(rutaMusica)) {
				std::cout << "Error al cargar la musicaFondo: Nivel" << std::endl;
			}
			_musicaFondo.play();
		}
	}
}



void Nivel::nivelDrawer(sf::RenderWindow& window)
{


	switch (_nivel) {
	case NIVELES::MENU:
		if (menuSi) {

			menu.draw(window);
		}
		else {
			setLevel(NIVELES::PRESET_NIVEL);
		}
		break;

	case NIVELES::NIVEL_1:

			window.setView(_vista);

			window.draw(*_background);

			if (_portalState == true) {
				window.draw(*_portal);
				window.draw(_portalAlert);

			}

			window.draw(*_map);

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
				if (auto rino = std::dynamic_pointer_cast<Rino>(aldeano)) {
					window.draw(rino->getSprite());
				}
			}


			for (int i = 0; i < _frutas.size(); i++) {
				window.draw(*_frutas[i]);
			}


			window.draw(*_personaje);

			///window.draw(_overlay);

			window.setView(window.getDefaultView());

			_ui->drawUi(window);

		break;
	case NIVELES::BOSS:

			window.setView(_vista);

			window.draw(*_background);

			window.draw(*_map);

			for (int i = 0; i < _plataformasN.size(); i++) {
				window.draw(_plataformasN[i]->getShape());
			}


			window.draw(*_personaje);

			for (int i = 0; i < _crystals.size(); i++) {
				window.draw(*_crystals[i]);
			}


			for (int i = 0; i < _tottems.size(); i++) {
				window.draw(*_tottems[i]);
			}

			window.draw(*mago);

			window.draw(_overlay);


			window.setView(window.getDefaultView());

			_ui->drawUi(window);

		break;
	case NIVELES::WIN:  // ******************************************* WIN LOSE DRAWER ************************************************

		menu.draw(window); // *************************************

		break;
	case NIVELES::LOSE:

		menu.draw(window);

		break;

	}


}


void Nivel::gameStateController(b2World& world)
{


	if (_nivel == NIVELES::NIVEL_1) {


			bool* _alive = _personaje->getVida();
			int time = _ui->getTime();

			if (_alive[0] == false || time >= 3) {
				std::cout << " LA PARTIDA HA TERMINADO - PERDISTE ! " << std::endl;
				_musicaFondo.stop();  // *****************************************			
				menu.setFrutasRecolectadas(frutasRecolectadas); // *********
				_nivel = NIVELES::LOSE;
				cleanLevel(world);
			}
			else if (_ui->getPoints() > 1000 && _nivel != NIVELES::BOSS && _portalState == false) {

				setPortal(world);
				_portalState = true;

			}
			else if (_portalState == true && _teleporting == true) {
				bossSetted = true;
				cleanLevel(world);
				_nivel = NIVELES::PRESET_BOSS;
	
			}
	

	}
	else if (_nivel == NIVELES::BOSS) {
		
		bool* _alive = _personaje->getVida();
		int time = _ui->getTime();
		bool mageLife = mago->isDeath();



		if (_alive[0] == false || time >= 3) {
			_musicaFondo.stop(); // *******************************************
			menu.setFrutasRecolectadas(frutasRecolectadas); 
			_nivel = NIVELES::LOSE;
			cleanLevel(world);
		}
		else if (mageLife == true) {
			_musicaFondo.stop(); // *******************************************
			menu.setFrutasRecolectadas(frutasRecolectadas); 
			_nivel = NIVELES::WIN;
			cleanLevel(world);

		}
		
	}

}

void Nivel::vistaSetViewPort(sf::FloatRect viewport, sf::RenderWindow& window) {
	/*
	_viewport = viewport;
	_vista.setViewport(viewport); // Ajusta el viewport para mantener la proporción
	window.setView(_vista);
	*/

}

void Nivel::cleanLevel(b2World& world) {


	if (_nivel == NIVELES::LOSE) {


		for (int i = 0; i < _plataformasN.size(); i++) {
			_plataformasN[i]->destroyBody(world);
		}


		////////////
		for (const auto& enemigo : enemigos) {
			if (auto calavera = std::dynamic_pointer_cast<Skull>(enemigo)) {
				calavera->destroyBody(world);
			}
			else if (auto conejo = std::dynamic_pointer_cast<Conejo>(enemigo)) { 
				conejo->destroyBody(world);
			}
		}

		for (const auto& aldeano : aldeanos) {
			if (auto tortuga = std::dynamic_pointer_cast<Tortuga>(aldeano)) {
				tortuga->destroyBody(world);
			}
			if (auto fatbird = std::dynamic_pointer_cast<Fatbird>(aldeano)) {
				fatbird->destroyBody(world);

			}
			if (auto rino = std::dynamic_pointer_cast<Rino>(aldeano)) {
				rino->destroyBody(world);
			}
		}

		for (int i = 0; i < _frutas.size(); i++) {
			_frutas[i]->destroyBody(world);
		}


		if (_portalState == true) {
			_portalState = false;
			_portal->destroyBody(world);
			_portal.reset();
		}

		if (bossSetted) {

			mago->destroyBody(world);
			mago.reset();

			for (int i = 0; i < _crystals.size(); i++) {
				_crystals[i]->destroyBody(world);
			}
			_crystals.clear();

			for (int i = 0; i < _tottems.size(); i++) {
				_tottems[i]->destroyBody(world);
			}
			_tottems.clear();

			bossSetted = false;
		}

		_personaje->destroyBody(world);
		enemigos.clear();
		aldeanos.clear();
		_frutas.clear();
		_plataformasN.clear();
		_map.reset();
		_background.reset();
		_personaje.reset();
		_ui.reset();
		///
	

	}
	else if (_nivel == NIVELES::NIVEL_1 && _teleporting == true) {
		for (const auto& enemigo : enemigos) {
			if (auto calavera = std::dynamic_pointer_cast<Skull>(enemigo)) {
				calavera->destroyBody(world);
			}
			else if (auto conejo = std::dynamic_pointer_cast<Conejo>(enemigo)) {
				conejo->destroyBody(world);
			}
		}

		for (const auto& aldeano : aldeanos) {
			if (auto tortuga = std::dynamic_pointer_cast<Tortuga>(aldeano)) {
				tortuga->destroyBody(world);
			}
			if (auto fatbird = std::dynamic_pointer_cast<Fatbird>(aldeano)) {
				fatbird->destroyBody(world);
			}
			if (auto rino = std::dynamic_pointer_cast<Rino>(aldeano)) {
				rino->destroyBody(world);
			}
		}

		for (int i = 0; i < _frutas.size(); i++) {
			_frutas[i]->destroyBody(world);
		}

		for (int i = 0; i < _plataformasN.size(); i++) {
			_plataformasN[i]->destroyBody(world);
		}


		_portal->destroyBody(world);

		enemigos.clear();
		aldeanos.clear();
		_frutas.clear();
		_plataformasN.clear();
		_map.reset();
		_background.reset();
		_portal.reset();
		_portalState = false;
		_teleporting = false;
		//clean = true;
	}	
	if (_nivel == NIVELES::WIN) {



		for (int i = 0; i < _plataformasN.size(); i++) {
			_plataformasN[i]->destroyBody(world);
		}

		for (int i = 0; i < _crystals.size(); i++) {
			_crystals[i]->destroyBody(world);
		}
		for (int i = 0; i < _tottems.size(); i++) {
			_tottems[i]->destroyBody(world);
		}
	

		_personaje->destroyBody(world);
		mago->destroyBody(world);


		_plataformasN.clear();
		_map.reset();
		_crystals.clear();
		_tottems.clear();
		_background.reset();
		_personaje.reset();
		_ui.reset();
		mago.reset();

		//std::cout << "Se realizo la limpieza de los vectores" << std::endl;
		//clean = true;
		bossSetted = false;
	}
	


}


void Nivel::setPortalAlert() {

	if (!font.loadFromFile("./assets/fonts/Pixelon.ttf")) {
		std::cout << "Error al cargar la fuente" << std::endl;
	}

	_portalAlert.setFont(font);
	_portalAlert.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
	_portalAlert.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
	_portalAlert.setOutlineThickness(5); // Grosor del contorno
	_portalAlert.setString("Un portal misterioso aparecio!");
	_portalAlert.setCharacterSize(70);

	_portalAlert.setFillColor(sf::Color(180, 80, 80, 255));
	_portalAlert.setPosition(130.0f, 1.0f);


}


Nivel::~Nivel()
{


}





