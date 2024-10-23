#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Plataformas.h"
#include "Enemigo.h"
#include "Skull.h"

void mappingLevel(int vec[30][40], int level);


void mappingPlatform(Plataformas* arrayPlataformas, int level);

void mappingEnemies(Enemigo* arrayEnemigos, int level);

