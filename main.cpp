#include <iostream>
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Personaje.h"
#include "Map.h"
////// PRUEBA DE CALAVERA ENEMIGO
#include "Enemigo.h"
#include "Skull.h"

using namespace std;




int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Against the Clock");
	window.setFramerateLimit(60);



	///////////TODO ESTO DEBERIA IR EN UNA CLASE NIVEL
	Map nivel1(1);
	backgroundTile tiled;
	Personaje jugador;
	Skull calavera("./assets/enemigos/Skull/Idle_Basic(52x54).png", sf::Vector2f(550.0f, 350.0f),sf::Vector2f(2.f,2.f), sf::Vector2u(8, 1), 0.09f);
	Skull calavera2("./assets/enemigos/Skull/Idle_2_(52x54).png", sf::Vector2f(500.0f, 150.0f), sf::Vector2f(2.f, 2.f), sf::Vector2u(8, 1), 0.09f);

	
	//// SE CREA UN CLOCK Y UN DELTA TIME PARA CONTROLAR LAS ANIMACIONES.
	float deltaTime = 0.0f;
	sf::Clock clock;


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

		/////ACTUALIZACION DE PERSONAJE Y DEL FONDO CON MOVIMIENTO
		tiled.backgroundUpdate();
		//jugador.personajeUpdate();

		//////////// ACTUALIZACION DE LA CALAVERA ANIMADA
		calavera.updateSkull(0,deltaTime);
		//calavera2.updateSkull(0, deltaTime);

		window.clear();

		window.draw(tiled);

		nivel1.mapDrawer(window);
		window.draw(calavera);
		//window.draw(calavera2);
		//window.draw(jugador);
		window.display();
	}

	return 0;
}