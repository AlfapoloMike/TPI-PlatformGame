#include <iostream>
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Personaje.h"
#include "Map.h"



using namespace std;




int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Against the Clock");
	window.setFramerateLimit(60);


	Map nivel1(1);
	backgroundTile tiled;
	Personaje jugador;
	


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		tiled.backgroundUpdate();
		jugador.personajeUpdate();

		window.clear();

		window.draw(tiled);

		nivel1.mapDrawer(window);
		window.draw(jugador);
		window.display();
	}

	return 0;
}