#include "Map.h"


Map::Map(int nivel) {

	_nivel = nivel;


	_mapVertex = new sf::VertexArray[1200];
	if (_mapVertex == nullptr) {
		return;
	}

	mappingLevel(_mappingLevel, nivel);


	createMapTiles();

	_texture.loadFromFile("Terrain_(16x16).png");


}

void Map::mapDrawer(sf::RenderWindow& window) {

	for (int i = 0; i < 1200; i++) {

		window.draw(_mapVertex[i], &_texture);

	}
}

void Map::createMapTiles() {


	int counter = 0;

	for (int y = 0; y < 30; y++) {
		for (int x = 0; x < 40; x++) {

			sf::VertexArray cuadro(sf::Quads, 4);

			int index = _mappingLevel[y][x];

			if (index > 0) {

				sf::Vector2i spriteCoords = spriteCoordFinder(index);

				cuadro[0].position = sf::Vector2f(x * 20.0f, y * 20.0f);
				cuadro[1].position = sf::Vector2f(x * 20.0f, (y * 20.f) + 20.f);
				cuadro[2].position = sf::Vector2f((x * 20.f) + 20.f, (y * 20.f) + 20.f);
				cuadro[3].position = sf::Vector2f((x * 20.f) + 20.f, y * 20.f);


				cuadro[0].texCoords = sf::Vector2f(spriteCoords.x * 16.0f, spriteCoords.y * 16.0f);
				cuadro[1].texCoords = sf::Vector2f(spriteCoords.x * 16.0f, (16.0f * spriteCoords.y) + 16.f);
				cuadro[2].texCoords = sf::Vector2f((16.0f * spriteCoords.x) + 16.f, (16.0f * spriteCoords.y) + 16.f);
				cuadro[3].texCoords = sf::Vector2f((16.0f * spriteCoords.x) + 16.f, spriteCoords.y * 16.0f);

				_mapVertex[counter] = cuadro;

			}

			counter++;
		}
	}



}

sf::Vector2i Map::spriteCoordFinder(int index)
{
	int accVueltas = 1;

	for (int y = 0; y < 11; y++) {
		for (int x = 0; x < 22; x++) {
			if (index == accVueltas) {
				sf::Vector2i coord(x, y);
				return coord;
			}
			accVueltas++;
		}
	}

}
