#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "PuntajeJugadorArchivo.h"
#include "PuntajeJugador.h"

class Ranking : public sf::Drawable {
public:
	Ranking();
	~Ranking();
	void update(bool& cambioEstado);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//void draw(sf::RenderWindow &window);


private:
	sf::Font font;

	sf::Texture _rankingTexture;
	sf::Sprite _rankingSprite;
	std::string _rutaImagen;

	sf::Text _rankingTitulo;
	sf::Text _rankingTituloSombra;
	sf::Text _puntajesText;
	sf::Text _jugadoresText;

	PuntajeJugadorArchivo archivo;
	PuntajeJugador top[5];
	std::string players;
	std::string scores;

	//std::string players = ""; // ???
	//std::string scores = ""; // ???  CONSULTAR Por que si las declaro aca(y no en update) Lo dibuja muchas veces.

	//sf::Music _rankingMusic;
};

