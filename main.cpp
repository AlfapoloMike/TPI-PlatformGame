#include <iostream>
#include <SFML/Graphics.hpp>
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "GameContactListener.h"
#include "Nivel.h"


using namespace std;



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Against the Clock");
	window.setFramerateLimit(60);
	srand((unsigned)time(NULL));


	//// SE CREA UN CLOCK Y UN DELTA TIME PARA CONTROLAR LAS ANIMACIONES.
	float deltaTime = 0.0f;
	sf::Clock clock;

	 // Definir la gravedad (ej. 9.8 m/s^2 hacia abajo)
	b2Vec2 gravity(0.0f, -9.8f);
	const float pixelMetro = 40.0f;

	// Crear el mundo Box2D con la gravedad definida
	b2World world(gravity);

	///// Creamos el Nivel con los parametros nivel = 1, el mundo como referencia, y pixeles por metro es decir 40px = 1 metro en este caso.
	Nivel newNivel(0, world, pixelMetro);

	GameContactListener _contactListener;
	world.SetContactListener(&_contactListener);


	while (window.isOpen())
	{

		///// DELTATIME SE GUARDA EL CLOCK COMO SEGUNDOS
		deltaTime = clock.restart().asSeconds();
		world.Step(1 / 60.0f, 6,3);


		sf::Event event;
		while (window.pollEvent(event))
		{
			newNivel.cmdNivel(event); // Agregado Ale

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				// Calcula el nuevo aspecto de la ventana
				float windowWidth = event.size.width;
				float windowHeight = event.size.height;
				float windowRatio = windowWidth / windowHeight;
				float viewRatio = 800.0f / 600.0f;

				sf::FloatRect viewport;

				if (windowRatio > viewRatio) {
					// La ventana es más ancha que la vista
					float width = viewRatio / windowRatio;
					viewport = sf::FloatRect((1.0f - width) / 2.0f, 0.0f, width, 1.0f);
				}
				else {
					// La ventana es más alta que la vista
					float height = windowRatio / viewRatio;
					viewport = sf::FloatRect(0.0f, (1.0f - height) / 2.0f, 1.0f, height);
				}
				///////ESTO ESTA SIN IMPLEMENTAR, ESTA COMENTADO EN NIVEL PORQUE LOS BORDES QUEDAN CON FRANJA NEGRA
				newNivel.vistaSetViewPort(viewport, window);
			}

		}


		newNivel.nivelUpdate(world, window, deltaTime);
		window.clear();


		newNivel.nivelDrawer(window);
		window.display();
	}

	return 0;
}