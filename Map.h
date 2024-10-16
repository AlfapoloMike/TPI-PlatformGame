#pragma once
#include <SFML/Graphics.hpp>
#include "MappingLevel.h"


class Map {

private:
	sf::VertexArray *_mapVertex=nullptr;
	sf::Texture _texture;
	int _mappingLevel[30][40]{};
	int _nivel = 0;

public:
	Map(int nivel);
	void mapDrawer(sf::RenderWindow& window);
	void createMapTiles();
	sf::Vector2i spriteCoordFinder(int index);

};
