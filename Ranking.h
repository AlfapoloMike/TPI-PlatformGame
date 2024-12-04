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
	std::string players;
	std::string scores;

};

