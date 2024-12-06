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
#include "Crystal.h"
#include "Tottem.h"
#include "Mage.h"
#include "Menu.h"
#include "Portal.h"


enum class NIVELES {
	NIVEL_1, NIVEL_2, NIVEL_3, MENU, BOSS, WIN, LOSE, PRESET_NIVEL, PRESET_BOSS
};

class Nivel : public sf::Drawable {

protected:
	/// Array de punteros Enemigo
	std::vector<std::shared_ptr<Enemigo>> enemigos;
	/// Array de punteros Aldeanos
	std::vector<std::shared_ptr<Aldeano>> aldeanos;

	/// mapa con las texturas del fondo

	std::unique_ptr<Map> _map;

	std::unique_ptr<Portal> _portal;

	/// plataformas segun nivel
	std::vector<std::unique_ptr<Plataformas>> _plataformasN;
	/// fondo segun nviel
	std::unique_ptr<backgroundTile> _background;

	std::unique_ptr<GameUi> _ui;

	/// indicador de nivel
	NIVELES _nivel = NIVELES::MENU;
	/// pixeles por metro para la conversion de box2d a sfml
	float _pixelMetro;
	/// corazones, puntos y tiempo dentro de la ui

	/// vector de punteros para las frutas
	std::vector<std::unique_ptr<Frutas>> _frutas;
	/// contador de tiempo para el spawn de frutas
	float _fruitSpawnerTime = 0;

	std::unique_ptr<Jugador> _personaje;
	//Jugador* _personaje = nullptr;

	//Aldeanos _aldeanos;
	sf::Vector2f _nivelSize = sf::Vector2f(1460.0f, 960.0f);
	sf::View _vista = sf::View(sf::FloatRect(0, 0, 800, 600));
	sf::Vector2f playerPosition;
	sf::Vector2f _vistaSize;
	sf::Sprite _mapaTest;
	sf::Texture textura;

	std::vector<std::unique_ptr<Crystal>> _crystals;

	std::vector<std::unique_ptr<Tottem>> _tottems;

	Mage* mago = nullptr;


	sf::FloatRect _viewport;

	// Agregado Ale
	Menu menu;
	bool menuSi = true;
	bool settingAll = true;
	bool bossSetted = false;
	bool _win = false;
	bool _lose = false;
	bool _portalState = false;
	bool _teleporting = false;
	bool clean = false;

	// Agregado Ale
	int frutasRecolectadas[8]{};
	PuntajeJugadorArchivo archivo;

	///TEST OPACIDAD
	sf::RectangleShape _overlay;

public:

	Nivel(int level, b2World& world, float pixelMetro);
	void setPlayer(b2World& world);
	void setPlayerView();
	void setEnemigos(b2World& world, float pixelMetro);
	void setFruits(b2World& world, float deltaTime);
	void setCrystals(b2World& world, float deltaTime);
	void setTottems(b2World& world, float deltaTime);
	void setMap(b2World& world);
	void setVillager(b2World& world, float pixelMetro);
	void setPortal(b2World& world);
	void nivelDrawer(sf::RenderWindow& window);
	void gameStateController(b2World& world);
	void vistaSetViewPort(sf::FloatRect viewport, sf::RenderWindow& window);
	void cleanLevel(b2World& world);
	void nivelUpdate(b2World& world, sf::RenderWindow& window, float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Agregado Ale
	void setLevel(NIVELES nivel);
	void cmdNivel(sf::Event& event);



	~Nivel();


};


/*
sf::View view(sf::FloatRect(0, 0, 800, 600)); // Vista original

while (window.isOpen()) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::Resized) {
			// Calcula el nuevo aspecto de la ventana
			float windowWidth = event.size.width;
			float windowHeight = event.size.height;
			float windowRatio = windowWidth / windowHeight;
			float viewRatio = 800.0f / 600.0f;

			sf::FloatRect viewport;

			if (windowRatio > viewRatio) {
				// La ventana es más ancha que la vista
				float width = viewRatio / windowRatio;
				viewport = sf::FloatRect((1.0f - width) / 2.0f, 0.0f, width, 1.0f);
			} else {
				// La ventana es más alta que la vista
				float height = windowRatio / viewRatio;
				viewport = sf::FloatRect(0.0f, (1.0f - height) / 2.0f, 1.0f, height);
			}

			view.setViewport(viewport); // Ajusta el viewport para mantener la proporción
			window.setView(view);
		}
	}

	window.clear();
	window.draw(yourDrawable); // Dibuja tu contenido
	window.display();
}


*/