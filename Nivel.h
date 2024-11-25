#pragma once
#include "Enemigo.h"
#include "Map.h"
#include "Frutas.h"
#include "Skull.h"
#include "MappingLevel.h"
#include "Background.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "Corazon.h"
#include "Conejo.h"
#include "GameUi.h"
#include "CollisionCategories.h"
#include "Jugador.h"
#include "Aldeano.h"
#include "Tortuga.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "FatBird.h"
#include "Rino.h"

enum NIVELES {
	NIVEL_1, NIVEL_2, NIVEL_3, MENU
};

class Nivel : public sf::Drawable {

protected:
	/// Array de punteros Enemigo
	std::vector<std::shared_ptr<Enemigo>> enemigos;
	/// Array de punteros Aldeanos
	std::vector<std::shared_ptr<Aldeano>> aldeanos;

	/// mapa con las texturas del fondo
	Map *_mapa =nullptr;
	/// plataformas segun nivel
	Plataformas* _plataformas = nullptr;
	std::vector<std::unique_ptr<Plataformas>> _plataformasN;
	/// fondo segun nviel
	backgroundTile _background;
	/// indicador de nivel
	NIVELES _nivel = NIVELES::MENU;
	/// pixeles por metro para la conversion de box2d a sfml
	float _pixelMetro;
	/// corazones, puntos y tiempo dentro de la ui
	GameUi _ui;
	/// vector de punteros para las frutas
	std::vector<std::unique_ptr<Frutas>> _frutas;
	/// contador de tiempo para el spawn de frutas
	float _fruitSpawnerTime = 0;

	Jugador *_personaje = nullptr;
	//Aldeanos _aldeanos;
	sf::Vector2f _nivelSize= sf::Vector2f(1460.0f, 960.0f);

	sf::View _vista = sf::View(sf::FloatRect(0, 0, 800, 600));
	sf::Vector2f _vistaSize;
	sf::Sprite _mapaTest;
	sf::Texture textura;


public:
	Nivel(int level, b2World& world, float pixelMetro);
	void setPlayer(b2World& world);
	void setPlayerView();
	void setEnemigos(b2World& world, float pixelMetro);
	void setFruits(b2World& world, float deltaTime);
	void setMap(b2World& world);
	void setVillager(b2World& world, float pixelMetro);
	void nivelDrawer(sf::RenderWindow& window);
	void enemiesCreator();
	void setUI();
	void gameStateController();
	void nivelUpdate(b2World& world, sf::RenderWindow& window, float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;



	~Nivel();

	//sf::Sprite getSpriteEnemigo(int enemigo);
	Plataformas getPlataforma(int plataforma);

};