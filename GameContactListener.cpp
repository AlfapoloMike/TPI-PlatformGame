#include "GameContactListener.h"



void GameContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	uint16_t categoryA = fixtureA->GetFilterData().categoryBits;
	uint16_t categoryB = fixtureB->GetFilterData().categoryBits;

	if ((categoryA & ENEMY) && (categoryB & WALL)||
		(categoryA & WALL) && (categoryB & ENEMY)) {

		if (contacting == false) {

		std::cout << "piso la plataforma" << std::endl;

		contacting = true;
		}
	}
}

void GameContactListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	uint16_t categoryA = fixtureA->GetFilterData().categoryBits;
	uint16_t categoryB = fixtureB->GetFilterData().categoryBits;

	std::cout << "EndContact: A=" << categoryA << " B=" << categoryB << std::endl;

	if ((categoryA & ENEMY) && (categoryB & WALL) || (categoryA & WALL) && (categoryB & ENEMY)) {
	//	std::cout << "Fin de contacto: " << (categoryA & ENEMY) << " - " << (categoryB & WALL) << std::endl;
		std::cout << "Fin de contacto: " << (categoryA & WALL) << " - " << (categoryB & ENEMY) << std::endl;
		contacting = false;
	}

}
