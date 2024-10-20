#include <iostream>
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Map.h"
////// PRUEBA DE CALAVERA ENEMIGO
#include "Enemigo.h"
#include "Skull.h"
///// PRUEBA FRUTAS
#include "Frutas.h"

using namespace std;




int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Against the Clock");
	window.setFramerateLimit(60);
	srand(time(NULL));


	///////////TODO ESTO DEBERIA IR EN UNA CLASE NIVEL
	Map nivel1(1);
	backgroundTile tiled;
	Skull calavera(sf::Vector2f(550.0f, 350.0f),sf::Vector2f(2.f,2.f));
	Frutas fruta1;
	Frutas fruta2;
	
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

		//////////// ACTUALIZACION DE LA CALAVERA ANIMADA
		calavera.updateSkull(0,deltaTime);
		//calavera2.updateSkull(0, deltaTime);
		fruta1.fruitUpdate(0, deltaTime);
		fruta2.fruitUpdate(0, deltaTime);
		int random = rand() % 8 + 1;

		window.clear();
		std::cout << "     " << random << "      ";
		window.draw(tiled);
		nivel1.mapDrawer(window);
		window.draw(calavera);
		//window.draw(calavera2);
		window.draw(fruta1);
		window.draw(fruta2);
		window.display();
	}

	return 0;
}