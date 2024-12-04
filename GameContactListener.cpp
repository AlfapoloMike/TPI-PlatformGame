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
	//// EL CALCULO ES FIXTURE A > FIXTURE B
	b2Vec2 normal = worldManifold.normal;

	//PUNTERO VACIO PARA GUARDAR EL PUNTERO DE JUGADOR<<<<<
	Jugador* player = nullptr;
	Conejo* conejo = nullptr;
	Plataformas* muro = nullptr;
	Plataformas* plataforma = nullptr;
	Skull* calavera = nullptr;
	Tortuga* turtle = nullptr;
	Fatbird* bird = nullptr;
	Frutas* fruta = nullptr;
	Rino* rino = nullptr;
	Crystal* crystal = nullptr;
	IceBall* iceball = nullptr;
	Tottem* tottem = nullptr;
	Portal* portal = nullptr;

	/***********************************************FATBIRD Y PLATAFORMAS****************************************************************/
	if ((categoryA & FATBIRD) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & FATBIRD)) {



		if (categoryA & FATBIRD) {

			if (bird = reinterpret_cast<Fatbird*>(bodyA->GetUserData().pointer)) {
			
				bird->setStateFloor();

			}
		}
		else if (categoryB & FATBIRD) {
			if (bird = reinterpret_cast<Fatbird*>(bodyB->GetUserData().pointer)) {
			
				bird->setStateFloor();

			}

		}



	}

	/***********************************************FATBIRD Y PLATAFORMAS****************************************************************/

	/*************************************************FATBIRD Y PLAYER**************************************************************/


	if ((categoryA & FATBIRD) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & FATBIRD)) {



		if (categoryA & PLAYER) {

			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			bird = reinterpret_cast<Fatbird*>(bodyB->GetUserData().pointer);
			
			if (player != nullptr && bird != nullptr) {


				if (normal.y < -0.7f) {
					bird->recibeDanio();
					player->setSaltos();
					player->rebote();
					contact->SetEnabled(false);
				}
				else {
					player->recibeDanio(2);
					player->setFilterDataPlayer(false);

					contact->SetEnabled(false);

				}

			}
		}
		else if (categoryB & PLAYER) {

			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
			bird = reinterpret_cast<Fatbird*>(bodyA->GetUserData().pointer);

			if (player != nullptr && bird !=nullptr) {

	
				if (normal.y > 0.7f) {
					bird->recibeDanio();
					player->setSaltos();
					player->rebote();
					contact->SetEnabled(false);
				}
				else {
					player->recibeDanio(2);
					player->setFilterDataPlayer(false);
					contact->SetEnabled(false);

				}
				



			}
		}


	}
	/*************************************************FATBIRD Y PLAYER**************************************************************/
	//*********************************** COLISIONES CON CALAVERA Y MURO **************************************

	if ((categoryA & SKULLS) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & SKULLS)) {



		if (categoryA & SKULLS) {


			if (calavera = reinterpret_cast<Skull*>(bodyA->GetUserData().pointer)) {

				if (normal.x > 0.0f || normal.x < 0.0f) {
					calavera->setNewDirection(true, false);

				}
				if (normal.y > 0.0f || normal.y < 0.0f) {
					calavera->setNewDirection(false, true);

				}
			}

		}
		else if (categoryB & SKULLS) {
			
			if (calavera = reinterpret_cast<Skull*>(bodyB->GetUserData().pointer)) {

				if (normal.x > 0.0f || normal.x < 0.0f) {
					calavera->setNewDirection(true, false);

				}
				if (normal.y > 0.0f || normal.y < 0.0f) {
					calavera->setNewDirection(false, true);

				}

			}
			
		}



	}
	//*********************************** COLISIONES CON CALAVERA Y MURO **************************************

	//*********************************** COLISIONES CON RINO Y MURO **************************************


	if ((categoryA & RINO) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & RINO)) {



		if (categoryA & RINO) {


			if (rino = reinterpret_cast<Rino*>(bodyA->GetUserData().pointer)) {


				if (normal.x > 0.5f) {

					rino->setNewDirectionL();
					std::cout << "toque derecha - rino=a" << std::endl;
				}
				else if (normal.x < 0.0f) {

					std::cout << "toque izquierda - rino=a" << std::endl;

					rino->setNewDirectionR();
				}
			}

		}
		else if (categoryB & RINO) {

			if (rino = reinterpret_cast<Rino*>(bodyB->GetUserData().pointer)) {


				if (normal.x > 0.0f) {
			
					std::cout << "toque izquierda - rino=a" << std::endl;
					rino->setNewDirectionR();

				}
				else if (normal.x < 0.5f) {

					std::cout << "toque derecha - rino=b" << std::endl;
					rino->setNewDirectionL();

				}

			}

		}



	}
	//*********************************** COLISIONES CON RINO Y MURO **************************************

	//*********************************** COLISIONES CON CONEJO Y MURO **************************************

	if ((categoryA & BUNNY) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & BUNNY)) {


		
		if (categoryA & BUNNY) {
			
			if (conejo = reinterpret_cast<Conejo*>(bodyA->GetUserData().pointer)) {

				conejo->setContact(true);

				if (normal.x > 0.0f) {
					

					conejo->setNewDirection(true);
				}
				else if (normal.x < 0.0f) {
					
					conejo->setNewDirection(false);

				}
			}
	
		}
		else if (categoryB & BUNNY) {

			if (conejo = reinterpret_cast<Conejo*>(bodyB->GetUserData().pointer)) {
				
				conejo->setContact(true);

				if (normal.x > 0.0f) {
					
					conejo->setNewDirection(true);
				}
				else if (normal.x < 0.0f) {
					
					conejo->setNewDirection(false);

				}
			}


		}
		


	}
	///////////////////////////// CONEJO - PLATAFORMAS

	if ((categoryA & BUNNY) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & BUNNY)) {


		if (categoryA & BUNNY) {
			conejo = reinterpret_cast<Conejo*>(bodyA->GetUserData().pointer);
			plataforma = reinterpret_cast<Plataformas*>(bodyB->GetUserData().pointer);
			
			b2Vec2 bordes = plataforma->getBorder();

			if (plataforma && conejo) {
				conejo->setBorderWalk(bordes.x, bordes.y);
			}


		}
		if (categoryB & BUNNY) {
			conejo = reinterpret_cast<Conejo*>(bodyB->GetUserData().pointer);
			plataforma = reinterpret_cast<Plataformas*>(bodyA->GetUserData().pointer);

			b2Vec2 bordes = plataforma->getBorder();

			if (plataforma && conejo) {
				
				conejo->setBorderWalk(bordes.x, bordes.y);

			}



		}


	}
	/***************************************COLISION CONEJO Y MURO************************************************************/
	/***************************************COLISION TORTUGA Y PLATAFORMA************************************************************/

	if ((categoryA & TURTLE) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & TURTLE)) {


		if (categoryA & TURTLE) {
			turtle = reinterpret_cast<Tortuga*>(bodyA->GetUserData().pointer);
			plataforma = reinterpret_cast<Plataformas*>(bodyB->GetUserData().pointer);

			b2Vec2 bordes = plataforma->getBorder();

			if (plataforma && turtle) {
				turtle->setBorderWalk(bordes.x, bordes.y);
			}


		}
		if (categoryB & TURTLE) {
			turtle = reinterpret_cast<Tortuga*>(bodyB->GetUserData().pointer);
			plataforma = reinterpret_cast<Plataformas*>(bodyA->GetUserData().pointer);

			b2Vec2 bordes = plataforma->getBorder();

			if (plataforma && turtle) {
				turtle->setBorderWalk(bordes.x, bordes.y);

			}



		}


	}

	/***************************************COLISION TORTUGA Y PLATAFORMA************************************************************/
	/****************************************COLISION TORTUGA Y MURO******************************************************************/

	if ((categoryA & TURTLE) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & TURTLE)) {



		if (categoryA & TURTLE) {
			turtle = reinterpret_cast<Tortuga*>(bodyA->GetUserData().pointer);
			if (turtle) {

				turtle->setContact(true);

				if (normal.x < 0.0f) {
					turtle->setNewDirection(true);
				}
				else if (normal.x > 0.0f) {
					turtle->setNewDirection(false);
				}
			}

		}
		else if (categoryB & TURTLE) {
			turtle = reinterpret_cast<Tortuga*>(bodyB->GetUserData().pointer);

			if (turtle) {
				turtle->setContact(true);

				//std::cout << "Normal: (" << normal.x << ", " << normal.y << ")" << std::endl;

				if (normal.x > 0.0f) {
					turtle->setNewDirection(true);
				}
				else if (normal.x < 0.0f) {
					turtle->setNewDirection(false);

				}
			}


		}



	}

	/****************************************COLISION TORTUGA Y MURO******************************************************************/

	/****************************************COLISION JUGADOR Y TORTUGA ******************************************************************/

	if ((categoryA & TURTLE) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & TURTLE)) {



		if (categoryA & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			turtle = reinterpret_cast<Tortuga*>(bodyB->GetUserData().pointer);
			if (player && turtle) {
				

				bool spikes = turtle->getSpikes();
				if (spikes == true) {

					player->recibeDanio(2);
					player->setFilterDataPlayer(false);
					player->setSaltos();
					contact->SetEnabled(false);


				}
				else if (spikes == false) {
					if (normal.y < 0.0) {
			
						turtle->recibeDanio();
						player->rebote();
						player->setSaltos();
						contact->SetEnabled(false);

					}
					else if (normal.y > 0.0) {
						player->recibeDanio(2);
						player->setFilterDataPlayer(false);
						contact->SetEnabled(false);
					}
				}

			}
		}
		else if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
			turtle = reinterpret_cast<Tortuga*>(bodyA->GetUserData().pointer);

			if (player && turtle) {

				bool spikes = turtle->getSpikes();
				if (spikes == true) {

						player->recibeDanio(2);
						player->setFilterDataPlayer(false);
						player->setSaltos();
						contact->SetEnabled(false);

					
				}else if (spikes == false) {
					if (normal.y < 0.0) {
						player->recibeDanio(2);
						player->setFilterDataPlayer(false);
						contact->SetEnabled(false);
					}
					else if (normal.y > 0.0) {
						
						turtle->recibeDanio();
						player->rebote();
						player->setSaltos();
						contact->SetEnabled(false);

					}
				}



			}
		}


	}

	/****************************************COLISION JUGADOR Y TORTUGA ******************************************************************/


	//*********************************** COLISIONES CON JUGADOR Y CONEJO **************************************


	if ((categoryA & RINO) && (categoryB & PLAYER)||
		(categoryA & PLAYER) && (categoryB & RINO)) {



		if (categoryA & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			if(player) {
				player->recibeDanio(2);
				player->setFilterDataPlayer(false);
				contact->SetEnabled(false);

			}
		}
		else if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (player) {

				player->recibeDanio(2);
				player->setFilterDataPlayer(false);
				contact->SetEnabled(false);


			}
		}


	}


	if ((categoryA & PORTAL) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & PORTAL)) {



		if (categoryA & PORTAL) {
			portal = reinterpret_cast<Portal*>(bodyA->GetUserData().pointer);
			if (portal) {
				std::cout << "esta tocando el portal" << std::endl;
				portal->setTouched();
				std::cout << "se seteo el contacto en: " << portal->isTouched() << std::endl;
				contact->SetEnabled(false);


			}
		}
		else if (categoryB & PORTAL) {
			portal = reinterpret_cast<Portal*>(bodyB->GetUserData().pointer);

			if (portal) {
				std::cout << "esta tocando el portal" << std::endl;
				portal->setTouched();
				std::cout << "se seteo el contacto en: " << portal->isTouched() << std::endl;

				contact->SetEnabled(false);


			}
		}


	}
	//*********************************** COLISIONES CON JUGADOR Y CONEJO **************************************

	if ((categoryA & BUNNY) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & BUNNY)) {



		if (categoryA & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			if (player) {
				player->recibeDanio(2);
				player->setFilterDataPlayer(false);
				contact->SetEnabled(false);

			}
		}
		else if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (player) {

				player->recibeDanio(2);
				player->setFilterDataPlayer(false);
				contact->SetEnabled(false);


			}
		}


	}

	
	//********************************** COLISIONES CON JUGADOR Y CALAVERA **************************************


	if ((categoryA & SKULLS) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & SKULLS)) {



		if (categoryA & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			if (player) {
				player->recibeDanio(1);
				player->setFilterDataPlayer(false);
				contact->SetEnabled(false);
			}
		}
		else if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (player) {

				player->recibeDanio(1);
				player->setFilterDataPlayer(false);
				contact->SetEnabled(false);
				
			}
		}


	}

	//********************************** COLISIONES CON JUGADOR Y CALAVERA **************************************

	//*********************************** COLISIONES CON JUGADOR Y PLATAFORMAS **************************************

	
	if ((categoryA & PLAYER) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & PLAYER)) {
		if (categoryA & PLAYER) {

			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);

			std::cout << "Normal: (" << normal.x << ", " << normal.y << ")" << std::endl;

			if (player) {
				if (normal.y < 0.0f)
				{
					player->setSaltos();
					player->setContactFloor(true);
					player->setInWall(false);

				}
			}

		}
		else if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			std::cout << "Normal: (" << normal.x << ", " << normal.y << ")" << std::endl;

			if (player) {
				if (normal.y > 0.0f)
				{

					player->setSaltos();
					player->setContactFloor(true);
					player->setInWall(false);

				}
			}


		}
	}

	
	//*********************************** COLISIONES CON JUGADOR Y PLATAFORMAS **************************************

		//*********************************** COLISIONES CON JUGADOR Y MUROS **************************************


	if ((categoryA & PLAYER) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);

			if (normal.x < 0.0f) {
				if (!player->getFloorContact()) {
					player->setInWall(true);
				}
			}
			else if (normal.x > 0.0f) {
				if (!player->getFloorContact()) {
					player->setInWall(true);
				}

			}
		
		}
		
		if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			if (normal.x > 0.0f) {
				if (!player->getFloorContact()) {
					player->setInWall(true);
				}
			}
			else if (normal.x < 0.0f) {
				if (!player->getFloorContact()) {
					player->setInWall(true);
				}

			}

		}
	}

	//*********************************** COLISIONES CON JUGADOR Y MUROS **************************************


	if ((categoryA & PLAYER) && (categoryB & LASER) ||
		(categoryA & LASER) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);

			player->recibeDanio(1);
			player->setFilterDataPlayer(false);
			contact->SetEnabled(false);

		}

		if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			player->recibeDanio(1);
			player->setFilterDataPlayer(false);
			contact->SetEnabled(false);


		}
	}

	if ((categoryA & PLAYER) && (categoryB & ICEBALL) ||
		(categoryA & ICEBALL) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			iceball = reinterpret_cast<IceBall*>(bodyB->GetUserData().pointer);

			if (player && iceball) {
				iceball->explodeBall();
				player->recibeDanio(1);
				player->setFilterDataPlayer(false);
				contact->SetEnabled(false);
			}
	

		}

		if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
			iceball = reinterpret_cast<IceBall*>(bodyA->GetUserData().pointer);
			if (player && iceball) {
				iceball->explodeBall();
				player->recibeDanio(1);
				player->setFilterDataPlayer(false);
				contact->SetEnabled(false);

			}
	


		}
	}


	if ((categoryA & CRYSTAL) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & CRYSTAL)) {

		if (categoryA & CRYSTAL) {
			crystal = reinterpret_cast<Crystal*>(bodyA->GetUserData().pointer);
			
			if (crystal) {
				if (crystal->isLaser()) {
					crystal->changeDirection();
				}
				else {
					//crystal->setRandomPosition();
					crystal->changeDirection();

				}
			}
		}

		if (categoryB & CRYSTAL) {
			crystal = reinterpret_cast<Crystal*>(bodyB->GetUserData().pointer);

			if (crystal) {
				if (crystal->isLaser()) {
					crystal->changeDirection();
				}
				else {
					//crystal->setRandomPosition();
					crystal->changeDirection();

				}
			}

		}
	}


	if ((categoryA & ICEBALL) && (categoryB & WALL) ||
		(categoryA & WALL) && (categoryB & ICEBALL)) {

		if (categoryA & ICEBALL) {
			iceball = reinterpret_cast<IceBall*>(bodyA->GetUserData().pointer);

			if (iceball) {

				if (normal.x > 0 || normal.x <0) {
					//iceball->setNewDirection(false, true);
					iceball->explodeBall();
				}
	
				if (normal.y > 0 || normal.y < 0) {
					//iceball->setNewDirection(true, false);
					iceball->explodeBall();

				}
	
			}
		}

		if (categoryB & ICEBALL) {
			iceball = reinterpret_cast<IceBall*>(bodyB->GetUserData().pointer);

			if (iceball) {
				if (normal.x > 0 || normal.x < 0) {
					//iceball->setNewDirection(true, false);
					iceball->explodeBall();

				}

				if (normal.y > 0 || normal.y < 0) {
					//iceball->setNewDirection(false, true);
					iceball->explodeBall();



				}
			}

		}
	}
	//*********************************** COLISIONES CON JUGADOR Y MUROS **************************************


	if ((categoryA & PLAYER) && (categoryB & LASER) ||
		(categoryA & LASER) && (categoryB & PLAYER)) {

		if (categoryA & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);

			std::cout << "Auch recibi danio" << std::endl;

		}

		if (categoryB & PLAYER) {
			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);

			std::cout << "Auch recibi danio" << std::endl;


		}
	}
	//*********************************** COLISIONES CON JUGADOR Y FRUTAS **************************************

	if ((categoryA & TOTTEMS) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & TOTTEMS)) {



		if (categoryA & PLAYER) {

			player = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
			tottem = reinterpret_cast<Tottem*>(bodyB->GetUserData().pointer);

			if (player != nullptr && tottem != nullptr) {


				if (normal.y < -0.7f) {
					tottem->setDestroyed();
					player->setSaltos();
					player->rebote();
					contact->SetEnabled(false);
				}
				else {
					std::cout << " LO TOQUE POR UN LADO QUE NO ES ARRIBA " << std::endl;
					contact->SetEnabled(false);
				}

			}
		}
		else if (categoryB & PLAYER) {

			player = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
			tottem = reinterpret_cast<Tottem*>(bodyA->GetUserData().pointer);

			if (player != nullptr && tottem != nullptr) {


				if (normal.y > 0.7f) {
					tottem->setDestroyed();
					player->setSaltos();
					player->rebote();
					contact->SetEnabled(false);
				}
				else {
					std::cout << " LO TOQUE POR UN LADO QUE NO ES ARRIBA " << std::endl;
					contact->SetEnabled(false);

				}




			}
		}


	}


	if ((categoryA & TOTTEMS) && (categoryB & PLATFORM) ||
		(categoryA & PLATFORM) && (categoryB & TOTTEMS)) {


		if (categoryA & TOTTEMS) {
			tottem = reinterpret_cast<Tottem*>(bodyA->GetUserData().pointer);
			tottem->setSpawning();
		}
		else if (categoryB & TOTTEMS) {
			tottem = reinterpret_cast<Tottem*>(bodyB->GetUserData().pointer);
			tottem->setSpawning();
		}



	}




	if ((categoryA & FRUITS) && (categoryB & PLAYER) ||
		(categoryA & PLAYER) && (categoryB & FRUITS)) {
		

		if (categoryA & FRUITS) {
			fruta = reinterpret_cast<Frutas*>(bodyA->GetUserData().pointer);
			fruta->setFruitPicked();
		}
		else if (categoryB & FRUITS) {
			fruta = reinterpret_cast<Frutas*>(bodyB->GetUserData().pointer);
			fruta->setFruitPicked();
		}



	}


}


void GameContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	// Obtén las fixtures y los cuerpos

	

	auto* fixtureA = contact->GetFixtureA();
	auto* fixtureB = contact->GetFixtureB();
	auto* bodyA = fixtureA->GetBody();
	auto* bodyB = fixtureB->GetBody();

	// Categorías de los cuerpos
	uint16 categoryA = fixtureA->GetFilterData().categoryBits;
	uint16 categoryB = fixtureB->GetFilterData().categoryBits;


};


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

