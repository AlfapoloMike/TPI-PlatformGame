#include <iostream>
#include <SFML/Graphics.hpp>
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "Background.h"
#include "Map.h"
////// PRUEBA DE CALAVERA ENEMIGO
#include "Enemigo.h" 
#include "Skull.h"
///// PRUEBA FRUTAS
#include "Frutas.h"
//// PRUEBA PLATAFORMAS
#include "Plataformas.h" 
/// INCLUYENDO EL NIVEL
#include "Nivel.h"
/// INCLUDE DE ALE
#include "Collisionable.h"
#include "Jugador.h"
#include "Aldeano.h"
#include "Tortuga.h"
#include "Conejo.h"

#include "GameUi.h"
#include "GameContactListener.h"


using namespace std;



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Against the Clock");
	window.setFramerateLimit(60);
	srand((unsigned)time(NULL));


	///////////TODO ESTO DEBERIA IR EN UNA CLASE NIVEL

	
	//// SE CREA UN CLOCK Y UN DELTA TIME PARA CONTROLAR LAS ANIMACIONES.
	float deltaTime = 0.0f;
	sf::Clock clock;



	
	Tortuga tortuga1(sf::Vector2f(300.0f, 468.0f), sf::Vector2f(0.f, 0.f)); ////****


	//////////////////////PRUEBAS DE BOX2D*********************************************

	 // Definir la gravedad (ej. 9.8 m/s^2 hacia abajo)
	b2Vec2 gravity(0.0f, -9.8f);
	const float pixelMetro = 40.0f;

	// Crear el mundo Box2D con la gravedad definida
	b2World world(gravity);

	///// Creamos el Nivel con los parametros nivel = 1, el mundo como referencia, y pixeles por metro es decir 40px = 1 metro en este caso.
	Nivel newNivel(1, world, pixelMetro);
	
	GameContactListener _contactListener;

	world.SetContactListener(&_contactListener);


	while (window.isOpen())
	{

		///// DELTATIME SE GUARDA EL CLOCK COMO SEGUNDOS
		deltaTime = clock.restart().asSeconds();
		world.Step(1 / 60.0f, 8, 5);
	

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			newNivel.playerEventHandler(event);
		}


		newNivel.nivelUpdate(world, window, deltaTime);

		tortuga1.update(0, deltaTime);


		window.clear();



		newNivel.nivelDrawer(window);
		window.draw(tortuga1);



		window.display();
	}
	
	return 0;
}