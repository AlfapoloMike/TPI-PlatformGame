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

using namespace std;




int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Against the Clock");
	window.setFramerateLimit(60);
	srand((unsigned)time(NULL));


	///////////TODO ESTO DEBERIA IR EN UNA CLASE NIVEL
	Map nivel1(1);
	backgroundTile tiled;
	Skull calavera(sf::Vector2f(550.0f, 350.0f),sf::Vector2f(2.f,2.f));
	Frutas fruta1;
	Frutas fruta2;
	
	//// SE CREA UN CLOCK Y UN DELTA TIME PARA CONTROLAR LAS ANIMACIONES.
	float deltaTime = 0.0f;
	sf::Clock clock;

	Nivel newNivel(1);

	Plataformas plataforma(sf::Vector2f(60, 480), sf::Vector2f(680, 60));
	Plataformas plataforma1(sf::Vector2f(60, 180), sf::Vector2f(80, 20));
	Plataformas plataforma2(sf::Vector2f(400, 240), sf::Vector2f(100, 20));
	Plataformas plataforma3(sf::Vector2f(340, 400), sf::Vector2f(400, 20));
	Plataformas plataforma4(sf::Vector2f(60, 180), sf::Vector2f(80, 20));
	Plataformas plataforma5(sf::Vector2f(660, 180), sf::Vector2f(80, 20));
	Plataformas plataforma6(sf::Vector2f(580, 280), sf::Vector2f(160, 20));
	Plataformas plataforma7(sf::Vector2f(160, 160), sf::Vector2f(80, 20));
	Plataformas plataforma8(sf::Vector2f(240, 220), sf::Vector2f(80, 20));
	Plataformas plataforma9(sf::Vector2f(520, 140), sf::Vector2f(80, 20));


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
		fruta1.fruitUpdate(0, deltaTime);
		fruta2.fruitUpdate(0, deltaTime);
		newNivel.nivelUpdate(window, deltaTime);

		window.clear();
		window.draw(tiled);

		//nivel1.mapDrawer(window);
		//window.draw(calavera);

		//window.draw(newNivel);
		window.draw(fruta1);
		window.draw(fruta2);

		window.draw(plataforma);
		window.draw(plataforma1);

		window.draw(plataforma2);

		window.draw(plataforma3);

		window.draw(plataforma4);

		window.draw(plataforma5);

		window.draw(plataforma6);

		window.draw(plataforma7);
		window.draw(plataforma8);

		window.draw(plataforma9);

		window.draw(newNivel);

		newNivel.nivelDrawer(window);

		window.display();
	}

	return 0;
}