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


	Map nivel1(1);
	backgroundTile tiled;
	Personaje jugador;
	Skull calavera("./assets/enemigos/Skull/Orange_Particle.png", sf::Vector2f(350.0f, 350.0f),sf::Vector2f(2.f,2.f));
	float deltaTime = 0.0f;
	sf::Clock clock;


	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		tiled.backgroundUpdate();
		jugador.personajeUpdate();
		calavera.updateSkull();

		window.clear();

		window.draw(tiled);

		nivel1.mapDrawer(window);
		window.draw(calavera);
		window.draw(jugador);
		window.display();
	}

	return 0;
}