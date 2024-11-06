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

#include "Corazon.h"
#include "GameUi.h"
using namespace std;







class TestBall {
public:
	TestBall(b2World& world, float startX, float startY, float radius = 1.0f) {
		// Definir el cuerpo dinámico
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(startX, startY);

		// Crear el cuerpo en el mundo
		ballBody = world.CreateBody(&bodyDef);

		// Definir la forma de la bola
		b2CircleShape circleShape;
		circleShape.m_radius = radius;

		// Configurar propiedades físicas
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 0.6f;

		// Asociar el fixture a la bola
		ballBody->CreateFixture(&fixtureDef);
	}

	// Obtener posición para verificar en la simulación
	b2Vec2 getPosition() const {
		return ballBody->GetPosition();
	}

	float getAngle() const {
		return ballBody->GetAngle();
	}

private:
	b2Body* ballBody;
};









int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Against the Clock");
	window.setFramerateLimit(60);
	srand((unsigned)time(NULL));


	///////////TODO ESTO DEBERIA IR EN UNA CLASE NIVEL

	
	//// SE CREA UN CLOCK Y UN DELTA TIME PARA CONTROLAR LAS ANIMACIONES.
	float deltaTime = 0.0f;
	sf::Clock clock;



	Jugador frogar(sf::Vector2f(100.0f, 100.0f)); ////****
	Tortuga tortuga1(sf::Vector2f(300.0f, 468.0f), sf::Vector2f(0.f, 0.f)); ////****


	//////////////////////PRUEBAS DE BOX2D*********************************************

	 // Definir la gravedad (ej. 9.8 m/s^2 hacia abajo)
	b2Vec2 gravity(0.0f, -9.8f);
	const float pixelMetro = 40.0f;

	// Crear el mundo Box2D con la gravedad definida
	b2World world(gravity);

	///// Creamos el Nivel con los parametros nivel = 1, el mundo como referencia, y pixeles por metro es decir 40px = 1 metro en este caso.
	Nivel newNivel(1, world, pixelMetro);
	
	
	///**************************************************************************************
	/////////
	////////                   TODO ESTO ES UNA DECLARACION PREDETERMINADA DE UNA ESFERA CON GRAVEDAD PARA PROBAR LAS PLATAFORMAS.
	////////
	const float SCALE = 40.0f; // Factor de conversión de Box2D (metros) a SFML (píxeles)
	const float WINDOW_WIDTH = 800.0f;
	const float WINDOW_HEIGHT = 600.0f;

		// Crear un cuerpo dinámico para la bola
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(12.9f,15.0f); // Posición inicial (en metros)
	b2Body* body = world.CreateBody(&bodyDef);

	// Crear una forma de círculo para el cuerpo de la bola
	b2CircleShape circleShape;
	circleShape.m_radius = 20.0f / SCALE; // Radio de la bola en metros (20 píxeles)

	// Crear una "fixture" para el cuerpo de la bola
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;    // Densidad para el cálculo de la masa
	fixtureDef.friction = 0.3f;   // Fricción al colisionar
	fixtureDef.restitution = 0.6f; // Rebote de la bola
	body->CreateFixture(&fixtureDef);

	// Crear el círculo SFML para la bola
	sf::CircleShape circle(20.0f); // Radio de 20 píxeles
	circle.setFillColor(sf::Color::Cyan);
	circle.setOrigin(20.0f, 20.0f); // Centrar el origen en el centro de la bola


	b2PolygonShape sensorShape;
	/////////**********************************************************************************************************************************
	///////// CONEJO
	///////// TEST
	/////////
	//Conejo rabbit(sf::Vector2f(3.0f, 13.0f), sf::Vector2f(0.5f, 0.5f), world, sf::Vector2f(0.85f, 1.1f),2.0f,15.0f,pixelMetro);
	/*****RECUADRO PARA VER AL CONEJO*******/
	sf::RectangleShape rect(sf::Vector2f(0.5*40*2,0.5*40*2)); // Radio de 20 píxeles
	rect.setFillColor(sf::Color::Cyan);
	rect.setOrigin(rect.getSize()/2.0f); // Centrar el origen en el centro de la bola


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


		newNivel.nivelUpdate(world, window, deltaTime);
		frogar.update();
		tortuga1.update(0, deltaTime);
		//rabbit.updateEnemie(0, deltaTime);



		// Colisiones ****************************************************
		// Con plataformas de Newnivel
		for (int i = 0; i < 10; i++) {
			if (frogar.getPrevPosition().y + frogar.getDraw().getGlobalBounds().height <= newNivel.getPlataforma(i).getBounds().top
				&&frogar.getDraw().getGlobalBounds().intersects(newNivel.getPlataforma(i).getBounds())
				&& frogar.getVelocidadSalto() < 0) {
			//	std::cout << "Colisión vertical Plataforma " << i + 1 << std::endl;
				frogar.quieto(frogar.getDraw().getPosition().x, newNivel.getPlataforma(i).getBounds().top - frogar.getDraw().getGlobalBounds().height);
			}

		}
		// Con tortuga
		if (frogar.isCollision(tortuga1)) {
			std::cout << "Colision con TORTUGA!!!!" << std::endl;
			if ((frogar.getPrevPosition().y + frogar.getBounds().height <= tortuga1.getBounds().top - 5) && frogar.getVelocidadSalto() < 0) {
			//	std::cout << "Colisión vertical TORTUGA (superior)!" << std::endl;
				frogar.mover(0, -23);
			}
		}
		// Con enemigos
		/*
		for (int i = 0; i < 3; i++) {
			sf::Sprite enemie = newNivel.getSpriteEnemigo(i);
			if (frogar.getDraw().getGlobalBounds().intersects(enemie.getGlobalBounds())) {
				//std::cout << "Colisión vertical CALAVERA " << i + 1 << std::endl;
			}
		}		
		*/
		// ******************************************************************
			
		////// ACA SE ESTA ACTUALIZANDO EL MUNDO 

		world.Step(1 / 60.0f, 8, 3);

		// Obtener la posición de la bola de Box2D y actualizar el círculo SFML
		//////// ACA SE ESTA ACTUALIZANDO EL SHAPE DE LA ESFERA DE PRUEBA
		b2Vec2 position = body->GetPosition();
		circle.setPosition(position.x * SCALE,600 - position.y * SCALE);


		////**************************//////////////
		//b2Vec2 positionRabbit = rabbit.getPositionBody();
		//rect.setPosition(positionRabbit.x * SCALE, 600 - positionRabbit.y * SCALE);
		

		//******************************************************************
		window.clear();



		newNivel.nivelDrawer(window);
		window.draw(frogar);
		window.draw(tortuga1);
		///****************************************************
		window.draw(circle); ////// DIBUJAMOS LA ESFERA DE PRUEBA.
		//window.draw(rect); ///////// DIBUJAMOS CAJA DE PRUEBA PARA CONEJO
		//window.draw(rabbit);
		///****************************************************



		window.display();
	}
	
	return 0;
}