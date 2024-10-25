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

		frogar.cmd();

		fruta1.fruitUpdate(0, deltaTime);
		fruta2.fruitUpdate(0, deltaTime);
		newNivel.nivelUpdate(window, deltaTime);
		frogar.update();
		tortuga1.update(0, deltaTime);

		// Colisiones ****************************************************
		// Con plataformas de Newnivel
		for (int i = 0; i < 10; i++) {
			if (frogar.getPrevPosition().y + frogar.getDraw().getGlobalBounds().height <= newNivel.getPlataforma(i).getBounds().top
				&&frogar.getDraw().getGlobalBounds().intersects(newNivel.getPlataforma(i).getBounds())
				&& frogar.getVelocidadSalto() < 0) {
				std::cout << "Colisión vertical Plataforma " << i + 1 << std::endl;
				frogar.quieto(frogar.getDraw().getPosition().x, newNivel.getPlataforma(i).getBounds().top - frogar.getDraw().getGlobalBounds().height);
			}

		}
		// Con tortuga
		if (frogar.isCollision(tortuga1)) {
			std::cout << "Colision con TORTUGA!!!!" << std::endl;
			if ((frogar.getPrevPosition().y + frogar.getBounds().height <= tortuga1.getBounds().top - 5) && frogar.getVelocidadSalto() < 0) {
				std::cout << "Colisión vertical TORTUGA (superior)!" << std::endl;
				frogar.mover(0, -23);
			}
		}
		// Con enemigos
		for (int i = 0; i < 3; i++) {
			sf::Sprite enemie = newNivel.getSpriteEnemigo(i);
			if (frogar.getDraw().getGlobalBounds().intersects(enemie.getGlobalBounds())) {
				std::cout << "Colisión vertical CALAVERA " << i + 1 << std::endl;
			}
		}		
		// ******************************************************************
				
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