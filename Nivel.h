#pragma once
#include "Enemigo.h"
#include "Map.h"
#include "Frutas.h"
#include "Skull.h"

enum NIVELES {
	NIVEL_1, NIVEL_2, NIVEL_3, MENU
};

class Nivel : public sf::Drawable{

private:
	//IColisionable *_enemigos=nullptr;
	Enemigo* _enemigos[3];
	//Aldeanos _aldeanos;
	//Personaje _personaje;
	Map _mapa;
	//Plataformas *_plataformas = nullptr;
	//Frutas *_frutas = nullptr;
	NIVELES _nivel = NIVELES::MENU;



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
