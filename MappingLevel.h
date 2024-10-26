#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Plataformas.h"
#include "Enemigo.h"
#include "Skull.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"


void mappingLevel(int vec[30][40], int level);


void mappingPlatform(Plataformas* arrayPlataformas, int level, b2World& world, float pixelMetro);

void mappingEnemies(Enemigo* arrayEnemigos, int level);

