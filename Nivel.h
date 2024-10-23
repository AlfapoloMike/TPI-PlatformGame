#pragma once
#include "Enemigo.h"
#include "Map.h"
#include "Frutas.h"
#include "Skull.h"
#include "MappingLevel.h"
#include "Background.h"

enum NIVELES {
	NIVEL_1, NIVEL_2, NIVEL_3, MENU
};

class Nivel : public sf::Drawable{

protected:
	Enemigo**_enemigos=nullptr;
	Map _mapa;
	Plataformas *_plataformas = nullptr;
	backgroundTile _background;
	NIVELES _nivel = NIVELES::MENU;

	//Aldeanos _aldeanos;
	//Personaje _personaje;
	//Frutas *_frutas = nullptr;



public:
	Nivel(int level);
	void setEnemigos();
	void setMap();
	void nivelDrawer(sf::RenderWindow& window);
	void enemiesCreator();
	void nivelUpdate(sf::RenderWindow& window, float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	~Nivel();



};
