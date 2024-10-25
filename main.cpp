#include <iostream>
#include <SFML/Graphics.hpp>
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


using namespace std;




int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Against the Clock");
	window.setFramerateLimit(60);
	srand((unsigned)time(NULL));


	///////////TODO ESTO DEBERIA IR EN UNA CLASE NIVEL
	Map nivel1(1);
	Frutas fruta1;
	Frutas fruta2;
	
	//// SE CREA UN CLOCK Y UN DELTA TIME PARA CONTROLAR LAS ANIMACIONES.
	float deltaTime = 0.0f;
	sf::Clock clock;

	Nivel newNivel(1);


	Jugador frogar(sf::Vector2f(100.0f, 100.0f)); ////****
	Tortuga tortuga1(sf::Vector2f(300.0f, 468.0f), sf::Vector2f(0.f, 0.f)); ////****



	while (window.isOpen())
	{

		///// DELTATIME SE GUARDA EL CLOCK COMO SEGUNDOS
		deltaTime = clock.restart().asSeconds();


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//frogar.cmd();

		fruta1.fruitUpdate(0, deltaTime);
		fruta2.fruitUpdate(0, deltaTime);
		newNivel.nivelUpdate(window, deltaTime);
		frogar.update();
		tortuga1.update(0, deltaTime);


		window.clear();



		newNivel.nivelDrawer(window);
		window.draw(fruta1);
		window.draw(fruta2);
		window.draw(frogar);
		window.draw(tortuga1);


		window.display();
	}

	return 0;
}