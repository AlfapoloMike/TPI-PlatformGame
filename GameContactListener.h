#pragma once
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "CollisionCategories.h"
#include <iostream>
#include "Conejo.h"
#include "Jugador.h"
#include "Frutas.h"
#include "Plataformas.h"
#include "Skull.h"
#include "Tortuga.h"
#include "FatBird.h"
#include "Rino.h"
#include "Laser.h"
#include "Crystal.h"

class GameContactListener : public b2ContactListener {

public:


	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

private:
	bool contacting = false;

};