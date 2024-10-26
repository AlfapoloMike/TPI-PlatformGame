#pragma once
#include "Enemigo.h"
#include "Map.h"
#include "Frutas.h"
#include "Skull.h"
#include "MappingLevel.h"
#include "Background.h"
#include "Collisionable.h"//****
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"


enum NIVELES {
	NIVEL_1, NIVEL_2, NIVEL_3, MENU
};

class Nivel : public sf::Drawable {

protected:
	Enemigo** _enemigos = nullptr;
	Map _mapa;
	Plataformas* _plataformas = nullptr;
	backgroundTile _background;
	NIVELES _nivel = NIVELES::MENU;
	float _pixelMetro;

	//Aldeanos _aldeanos;
	//Personaje _personaje;
	//Frutas *_frutas = nullptr;



public:
	Nivel(int level, b2World& world, float pixelMetro);
	void setEnemigos();
	void setMap(b2World& world);
	void nivelDrawer(sf::RenderWindow& window);
	void enemiesCreator();
	void nivelUpdate(sf::RenderWindow& window, float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~Nivel();

	sf::Sprite getSpriteEnemigo(int enemigo);
	Plataformas getPlataforma(int plataforma);

};