#include "GameContactListener.h"



void GameContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();



	uint16_t categoryA = fixtureA->GetFilterData().categoryBits;
	uint16_t categoryB = fixtureB->GetFilterData().categoryBits;
	////GUARDAMOS AMBOS CUERPOS
	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);
	//// GUARDAMOS UN VECTOR QUE INDICA LA DIRECCION EN LA QUE LOS DOS CUERPOS COLISIONAN, LO GUARDA COMO UN VECTOR
	b2Vec2 normal = worldManifold.normal;

	//PUNTERO VACIO PARA GUARDAR EL PUNTERO DE JUGADOR<<<<<
	Jugador* player = nullptr;
	Conejo* conejo = nullptr;
	Plataformas* muro = nullptr;
	Plataformas* plataforma = nullptr;

	//*********************************** COLISIONES CON CONEJO Y MURO **************************************

	if ((categoryA & ENEMY) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & ENEMY)) {


		
		if (categoryA & ENEMY) {
			conejo = reinterpret_cast<Conejo*>(bodyA->GetUserData().pointer);
			//std::cout << "contacto";
			conejo->setContact(true);

			if (normal.x > 0.0f) {
				//	std::cout << "Colisión: Lado derecho de BodyA" << std::endl;
				conejo->setNewDirection(true);
				std::cout << "Tocamos el lado derecho" << std::endl;
			}
			else if (normal.x < 0.0f) {
				//	std::cout << "Colisión: Lado izquierdo de BodyA" << std::endl;
				conejo->setNewDirection(false);

				std::cout << "Tocamos el lado izquierdo" << std::endl;

			}
		}
		else if (categoryB & ENEMY) {
			conejo = reinterpret_cast<Conejo*>(bodyB->GetUserData().pointer);
			conejo->setContact(true);


			//std::cout << "contacto";

			if (normal.x > 0.0f) {
				//	std::cout << "Colisión: Lado derecho de BodyA" << std::endl;
				conejo->setNewDirection(true);

				std::cout << "Tocamos el lado derecho" << std::endl;
			}
			else if (normal.x < 0.0f) {
				//	std::cout << "Colisión: Lado izquierdo de BodyA" << std::endl;
				conejo->setNewDirection(false);

				std::cout << "Tocamos el lado izquierdo" << std::endl;

			}

		}
		


	}
	///////////////////////////// CONEJO - PLATAFORMAS

	if ((categoryA & ENEMY) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & ENEMY)) {

		Plataformas* plataforma2 = nullptr;


		if (categoryA & ENEMY) {
			conejo = reinterpret_cast<Conejo*>(bodyA->GetUserData().pointer);
			plataforma2 = reinterpret_cast<Plataformas*>(bodyB->GetUserData().pointer);
			
			b2Vec2 bordes = plataforma2->getBorder();

			if (plataforma2) {
				conejo->setBorderWalk(bordes.x, bordes.y);

				std::cout << "Esta plataforma es body B" << std::endl;
				std::cout << " Borde izq: " << bordes.x << " Borde der:" << bordes.y << std::endl;
			}


		}
		if (categoryB & ENEMY) {
			conejo = reinterpret_cast<Conejo*>(bodyB->GetUserData().pointer);
			plataforma2 = reinterpret_cast<Plataformas*>(bodyA->GetUserData().pointer);

			b2Vec2 bordes = plataforma2->getBorder();

			if (plataforma2) {
				
				conejo->setBorderWalk(bordes.x, bordes.y);

				std::cout << "Esta plataforma es body B" << std::endl;
				std::cout << " Borde izq: " << bordes.x << " Borde der:" << bordes.y << std::endl;



			}



		}


	}


	//*********************************** COLISIONES CON JUGADOR Y CONEJO **************************************


	if ((categoryA & ENEMY) && (categoryB & PLAYER)||
		(categoryA & PLAYER) && (categoryB & ENEMY)) {



		if (categoryA & PLAYER) {
			//std::cout << "PUNTERO DE A --- " << bodyA->GetUserData().pointer << std::endl;
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			if(player != nullptr) {
				if (normal.x > 0.0f) {
				//	std::cout << "Colisión: Lado derecho de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(ENEMY, false);

				}
				else if (normal.x < 0.0f) {
				//	std::cout << "Colisión: Lado izquierdo de BodyA" << std::endl;
					player->recibeDanio(1);
					player->setFilterDataPlayer(ENEMY, false);

				}

				if (normal.y > 0.0f) {
				//	std::cout << "Colisión: Parte superior de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(ENEMY, false);
				}
				else if (normal.y < 0.0f) {
				//	std::cout << "Colisión: Parte inferior de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(ENEMY, false);
				}
			}
		}
		else if (categoryB & PLAYER) {
			//std::cout << "PUNTERO DE B --- " << bodyB->GetUserData().pointer << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (player != nullptr) {

	
				// Aplicamos el impulso hacia atrás en el personaje
				//std::cout << "Impulso aplicado hacia atrás." << std::endl;
				if (normal.x > 0.0f) {
					//	std::cout << "Colisión: Lado derecho de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(ENEMY, false);


				}
				else if (normal.x < 0.0f) {
					//	std::cout << "Colisión: Lado izquierdo de BodyA" << std::endl;
					player->recibeDanio(1);
					player->setFilterDataPlayer(ENEMY, false);

				}

				if (normal.x > 0.0f && normal.y <0) {
					//std::cout << "Colisión: Lado derecho de BodyA" << std::endl;
					player->recibeDanio(1);
					player->setFilterDataPlayer(ENEMY, false);


				}
				else if (normal.x < 0.0f && normal.y < 0) {
					//std::cout << "Colisión: Lado izquierdo de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(ENEMY, false);



				}
			}
		}


	}

	//*********************************** COLISIONES CON JUGADOR Y CONEJO **************************************


	//*********************************** COLISIONES CON JUGADOR Y PLATAFORMAS **************************************


	if ((categoryA & PLAYER) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			//std::cout << "Categoria A es jugador" << std::endl;
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);

			if (normal.y > 0.0f) {
				//std::cout << "Colisión: Parte superior de BodyA" << std::endl;
				player->setSaltos();
				player->setContactFloor(true);
				player->setInWall(false);

			}
			else if (normal.y < 0.0f) {
				//std::cout << "Colisión: Parte inferior de BodyA" << std::endl;
			}
		}
		if (categoryB & PLAYER) {
			//std::cout << "Categoria B es jugador " << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (normal.y > 0.0f) {
				//std::cout << "Colisión: Parte superior de BodyA" << std::endl;
				player->setSaltos();
				player->setContactFloor(true);
				player->setInWall(false);

			}
			else if (normal.y < 0.0f) {
			//	std::cout << "Colisión: Parte inferior de BodyA" << std::endl;
			}
		}
	}
	//*********************************** COLISIONES CON JUGADOR Y PLATAFORMAS **************************************

		//*********************************** COLISIONES CON JUGADOR Y MUROS **************************************


	if ((categoryA & PLAYER) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			//std::cout << "Categoria A es jugador" << std::endl;
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			if (!player->getFloorContact()) {
				player->setInWall(true);
			}

		
		}
		
		if (categoryB & PLAYER) {
			//std::cout << "Categoria B es jugador " << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (!player->getFloorContact()) {
				player->setInWall(true);
			}

		}
	}

	//*********************************** COLISIONES CON JUGADOR Y MUROS **************************************



	//*********************************** COLISIONES CON JUGADOR Y FRUTAS **************************************

	Frutas* fruta = nullptr;

	if ((categoryA & FRUITS) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & FRUITS)) {



		std::cout << "Agarro la fruta" << std::endl;
		fruta = reinterpret_cast<Frutas*>(bodyB->GetUserData().pointer);

		if (categoryA & FRUITS) {
			fruta->setFruitPicked();
		}else if (categoryB & FRUITS) {
			fruta->setFruitPicked();

		}
	}
}

void GameContactListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	uint16_t categoryA = fixtureA->GetFilterData().categoryBits;
	uint16_t categoryB = fixtureB->GetFilterData().categoryBits;



	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);
	//// GUARDAMOS UN VECTOR QUE INDICA LA DIRECCION EN LA QUE LOS DOS CUERPOS COLISIONAN, LO GUARDA COMO UN VECTOR
	b2Vec2 normal = worldManifold.normal;


	///// PUNTERO VACIO PARA RECIBIR EL PUNTERO DEL JUGADOR, Y ASI UTILIZARLO.
	Jugador* player = nullptr;


	//std::cout << "EndContact: A=" << categoryA << " B=" << categoryB << std::endl;

	if ((categoryA & ENEMY) && (categoryB & WALL) || (categoryA & WALL) && (categoryB & ENEMY)) {
	//	std::cout << "Fin de contacto: " << (categoryA & ENEMY) << " - " << (categoryB & WALL) << std::endl;
		//std::cout << "Fin de contacto: " << (categoryA & WALL) << " - " << (categoryB & ENEMY) << std::endl;
		contacting = false;
	}




	/////////////////// CONTROL DE PERSONAJE DEJANDO DE CONTACTAR CON UNA PLATAFORMA ///////////////

	if ((categoryA & PLAYER) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			std::cout << "Categoria A es jugador" << std::endl;
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			player->setContactFloor(false);

		}
		if (categoryB & PLAYER) {
			std::cout << "Categoria B es jugador " << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
			player->setContactFloor(false);
			

		}
	}




	if ((categoryA & PLAYER) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			//std::cout << "Categoria A es jugador" << std::endl;
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			if (!player->getFloorContact()) {
				player->setSaltos();
				player->setInWall(false);
			}

		}

		if (categoryB & PLAYER) {
			//std::cout << "Categoria B es jugador " << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (!player->getFloorContact()) {
				player->setSaltos();
				player->setInWall(false);

			}

		}
	}
}
