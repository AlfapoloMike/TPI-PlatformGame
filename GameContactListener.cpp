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
	Skull* calavera = nullptr;

	if ((categoryA & SKULLS) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & SKULLS)) {



		if (categoryA & SKULLS) {
			calavera = reinterpret_cast<Skull*>(bodyA->GetUserData().pointer);
			//std::cout << "contacto";
			conejo->setContact(true);

			if (normal.x > 0.0f) {
				//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
				calavera->setNewDirection(true, false);

			}
			else if (normal.x < 0.0f) {
				//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
				calavera->setNewDirection(true, false);


			}
			if (normal.y > 0.0f) {
				calavera->setNewDirection(false, true);

			}
			else if (normal.y < 0.0f) {
				calavera->setNewDirection(false, true);
			}
		}
		else if (categoryB & SKULLS) {
			calavera = reinterpret_cast<Skull*>(bodyB->GetUserData().pointer);
			
			//std::cout << "contacto";

			if (normal.x > 0.0f) {
				//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
				calavera->setNewDirection(true, false);

			}
			else if (normal.x < 0.0f) {
				//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;

				calavera->setNewDirection(true, false);

			}
			if (normal.y > 0.0f) {
				calavera->setNewDirection(false, true);

			}
			else if (normal.y < 0.0f) {
				calavera->setNewDirection(false, true);

			}
		}



	}
	
	//*********************************** COLISIONES CON CONEJO Y MURO **************************************

	if ((categoryA & BUNNY) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & BUNNY)) {


		
		if (categoryA & BUNNY) {
			conejo = reinterpret_cast<Conejo*>(bodyA->GetUserData().pointer);
			//std::cout << "contacto";
			conejo->setContact(true);

			if (normal.x > 0.0f) {
				//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
				conejo->setNewDirection(true);
				std::cout << "Tocamos el lado derecho" << std::endl;
			}
			else if (normal.x < 0.0f) {
				//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
				conejo->setNewDirection(false);

				std::cout << "Tocamos el lado izquierdo" << std::endl;

			}
		}
		else if (categoryB & BUNNY) {
			conejo = reinterpret_cast<Conejo*>(bodyB->GetUserData().pointer);
			conejo->setContact(true);


			//std::cout << "contacto";

			if (normal.x > 0.0f) {
				//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
				conejo->setNewDirection(true);

				std::cout << "Tocamos el lado derecho" << std::endl;
			}
			else if (normal.x < 0.0f) {
				//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
				conejo->setNewDirection(false);

				std::cout << "Tocamos el lado izquierdo" << std::endl;

			}

		}
		


	}
	///////////////////////////// CONEJO - PLATAFORMAS

	if ((categoryA & BUNNY) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & BUNNY)) {

		Plataformas* plataforma2 = nullptr;


		if (categoryA & BUNNY) {
			conejo = reinterpret_cast<Conejo*>(bodyA->GetUserData().pointer);
			plataforma2 = reinterpret_cast<Plataformas*>(bodyB->GetUserData().pointer);
			
			b2Vec2 bordes = plataforma2->getBorder();

			if (plataforma2) {
				conejo->setBorderWalk(bordes.x, bordes.y);
			}


		}
		if (categoryB & BUNNY) {
			conejo = reinterpret_cast<Conejo*>(bodyB->GetUserData().pointer);
			plataforma2 = reinterpret_cast<Plataformas*>(bodyA->GetUserData().pointer);

			b2Vec2 bordes = plataforma2->getBorder();

			if (plataforma2) {
				
				conejo->setBorderWalk(bordes.x, bordes.y);

			}



		}


	}


	//*********************************** COLISIONES CON JUGADOR Y CONEJO **************************************


	if ((categoryA & BUNNY) && (categoryB & PLAYER)||
		(categoryA & PLAYER) && (categoryB & BUNNY)) {



		if (categoryA & PLAYER) {
			//std::cout << "PUNTERO DE A --- " << bodyA->GetUserData().pointer << std::endl;
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			if(player != nullptr) {
				player->recibeDanio(2);
				player->setFilterDataPlayer(BUNNY, false);
				contact->SetEnabled(false);
				/*
				if (normal.x > 0.0f) {
				//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(BUNNY, false);
					contact->SetEnabled(false);

				}
				else if (normal.x < 0.0f) {
				//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
					player->recibeDanio(1);
					player->setFilterDataPlayer(BUNNY, false);
					contact->SetEnabled(false);

				}

				if (normal.y > 0.0f) {
				//	std::cout << "Colisi�n: Parte superior de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(BUNNY, false);
					contact->SetEnabled(false);

				}
				else if (normal.y < 0.0f) {
				//	std::cout << "Colisi�n: Parte inferior de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(BUNNY, false);
					contact->SetEnabled(false);

				}
				*/
			}
		}
		else if (categoryB & PLAYER) {
			//std::cout << "PUNTERO DE B --- " << bodyB->GetUserData().pointer << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (player != nullptr) {

				player->recibeDanio(2);
				player->setFilterDataPlayer(BUNNY, false);
				contact->SetEnabled(false);
				// Aplicamos el impulso hacia atr�s en el personaje
				//std::cout << "Impulso aplicado hacia atr�s." << std::endl;
				/*
				if (normal.x > 0.0f) {
					//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(BUNNY, false);
					contact->SetEnabled(false);


				}
				else if (normal.x < 0.0f) {
					//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
					player->recibeDanio(1);
					player->setFilterDataPlayer(BUNNY, false);
					contact->SetEnabled(false);

				}

				if (normal.x > 0.0f && normal.y <0) {
					//std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
					player->recibeDanio(1);
					player->setFilterDataPlayer(BUNNY, false);
					contact->SetEnabled(false);


				}
				else if (normal.x < 0.0f && normal.y < 0) {
					//std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(BUNNY, false);
					contact->SetEnabled(false);



				}
				*/
			}
		}


	}

	//*********************************** COLISIONES CON JUGADOR Y CONEJO **************************************
	//********************************** COLISIONES CON JUGADOR Y CALAVERA **************************************


	if ((categoryA & SKULLS) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & SKULLS)) {



		if (categoryA & PLAYER) {
			//std::cout << "PUNTERO DE A --- " << bodyA->GetUserData().pointer << std::endl;
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			if (player != nullptr) {
				player->recibeDanio(1);
				player->setFilterDataPlayer(SKULLS, false);
				contact->SetEnabled(false);
				/*
				if (normal.x > 0.0f) {
					//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(SKULLS, false);
					contact->SetEnabled(false);

				}
				else if (normal.x < 0.0f) {
					//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
					player->recibeDanio(1);
					player->setFilterDataPlayer(SKULLS, false);
					contact->SetEnabled(false);

				}

				if (normal.y > 0.0f) {
					//	std::cout << "Colisi�n: Parte superior de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(SKULLS, false);
					contact->SetEnabled(false);
				}
				else if (normal.y < 0.0f) {
					//	std::cout << "Colisi�n: Parte inferior de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(SKULLS, false);
					contact->SetEnabled(false);
				}
				*/
			}
		}
		else if (categoryB & PLAYER) {
			//std::cout << "PUNTERO DE B --- " << bodyB->GetUserData().pointer << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (player != nullptr) {

				player->recibeDanio(1);
				player->setFilterDataPlayer(SKULLS, false);
				contact->SetEnabled(false);
				// Aplicamos el impulso hacia atr�s en el personaje
				//std::cout << "Impulso aplicado hacia atr�s." << std::endl;
				/*
				if (normal.x > 0.0f) {
					//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(SKULLS, false);
					contact->SetEnabled(false);

				}
				else if (normal.x < 0.0f) {
					//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
					player->recibeDanio(1);
					player->setFilterDataPlayer(SKULLS, false);
					contact->SetEnabled(false);
				}

				if (normal.x > 0.0f && normal.y < 0) {
					//std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
					player->recibeDanio(1);
					player->setFilterDataPlayer(SKULLS, false);
					contact->SetEnabled(false);

				}
				else if (normal.x < 0.0f && normal.y < 0) {
					//std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
					player->recibeDanio(2);
					player->setFilterDataPlayer(SKULLS, false);
					contact->SetEnabled(false);


				}
				*/
			}
		}


	}

	//********************************** COLISIONES CON JUGADOR Y CALAVERA **************************************

	//*********************************** COLISIONES CON JUGADOR Y PLATAFORMAS **************************************


	if ((categoryA & PLAYER) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			//std::cout << "Categoria A es jugador" << std::endl;
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);

			if (normal.y > 0.0f) {
				//std::cout << "Colisi�n: Parte superior de BodyA" << std::endl;
				player->setSaltos();
				player->setContactFloor(true);
				player->setInWall(false);

			}
			else if (normal.y < 0.0f) {
				//std::cout << "Colisi�n: Parte inferior de BodyA" << std::endl;
			}
		}
		if (categoryB & PLAYER) {
			//std::cout << "Categoria B es jugador " << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (normal.y > 0.0f) {
				//std::cout << "Colisi�n: Parte superior de BodyA" << std::endl;
				player->setSaltos();
				player->setContactFloor(true);
				player->setInWall(false);

			}
			else if (normal.y < 0.0f) {
			//	std::cout << "Colisi�n: Parte inferior de BodyA" << std::endl;
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
			/*
			if (!player->getFloorContact()) {
				player->setInWall(true);
			}
			*/

			if (normal.x > 0.0f) {
				//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
				if (!player->getFloorContact()) {
					player->setInWall(true);
				}
			}
			else if (normal.x < 0.0f) {
				//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
				if (!player->getFloorContact()) {
					player->setInWall(true);
				}

			}
		
		}
		
		if (categoryB & PLAYER) {
			//std::cout << "Categoria B es jugador " << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
			/*
			if (!player->getFloorContact()) {
				player->setInWall(true);
			}
			*/

			if (normal.x > 0.0f) {
				//	std::cout << "Colisi�n: Lado derecho de BodyA" << std::endl;
				if (!player->getFloorContact()) {
					player->setInWall(true);
				}
			}
			else if (normal.x < 0.0f) {
				//	std::cout << "Colisi�n: Lado izquierdo de BodyA" << std::endl;
				if (!player->getFloorContact()) {
					player->setInWall(true);
				}

			}

		}
	}

	//*********************************** COLISIONES CON JUGADOR Y MUROS **************************************



	//*********************************** COLISIONES CON JUGADOR Y FRUTAS **************************************

	Frutas* fruta = nullptr;

	if ((categoryA & FRUITS) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & FRUITS)) {
		fruta = reinterpret_cast<Frutas*>(bodyB->GetUserData().pointer);

		if (categoryA & FRUITS) {
			fruta->setFruitPicked();
		}
		else if (categoryB & FRUITS) {
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

	if ((categoryA & BUNNY) && (categoryB & WALL) || (categoryA & WALL) && (categoryB & BUNNY)) {
	//	std::cout << "Fin de contacto: " << (categoryA & ENEMY) << " - " << (categoryB & WALL) << std::endl;
		//std::cout << "Fin de contacto: " << (categoryA & WALL) << " - " << (categoryB & ENEMY) << std::endl;
		contacting = false;
	}




	/////////////////// CONTROL DE PERSONAJE DEJANDO DE CONTACTAR CON UNA PLATAFORMA ///////////////

	if ((categoryA & PLAYER) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			player->setContactFloor(false);

		}
		if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
			player->setContactFloor(false);
			

		}
	}




	if ((categoryA & PLAYER) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			//std::cout << "Categoria A es jugador" << std::endl;
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			if (!player->getFloorContact() && player->getWallContact() == true) {
				player->setSaltos();
				player->setInWall(false);
			}

		}

		if (categoryB & PLAYER) {
			//std::cout << "Categoria B es jugador " << std::endl;
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (!player->getFloorContact() && player->getWallContact() == true) {
				player->setSaltos();
				player->setInWall(false);

			}

		}
	}
}
