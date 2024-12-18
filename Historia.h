#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Historia : public sf::Drawable {

public:
	Historia();
	~Historia();
	void update(bool& _completa, bool& noComenzar);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void resetAll();


private:
	sf::Texture _historiaTexture;
	sf::Sprite _historiaSprite;
	std::string _rutaImagen;

	sf::Font font;

	sf::Text _historiaTitulo;
	sf::Text _historiaTituloSombra;
	sf::Text _historiaText;
	sf::Text _historiaPress;
	sf::Text storyTextDisplay;
	std::string _historia = "";

	sf::Clock _clockHistoria;  // Reloj para regular el tiempo de aparicion de letras
	std::string _textoMostrado; // Texto mostrado hasta ahora
	int _letraActual = 0;   // �ndice del car�cter que estamos mostrando actualmente

};