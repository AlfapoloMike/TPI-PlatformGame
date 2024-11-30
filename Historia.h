#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Historia : public sf::Drawable {

public:
	Historia();
	~Historia();
	void update(bool& _completa, bool& noComenzar);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::Texture _historiaTexture;
	sf::Sprite _historiaSprite;
	std::string _rutaImagen;

	sf::Font font;

	sf::Text _historiaTitulo;
	sf::Text _historiaTituloSombra;
	sf::Text _historiaText;
	sf::Text _historiaPress;
	std::string _historia = "";

	sf::Clock _clockHistoria;               // Reloj para medir el tiempo
	std::string _textoMostrado; // Texto mostrado hasta ahora
	int _letraActual = 0;   // Índice del carácter que estamos mostrando actualmente

};