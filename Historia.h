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

	sf::Clock clock;               // Reloj para medir el tiempo
	//float timePerLetter = 0.02f;   // Tiempo entre letras, puedes ajustarlo seg�n necesites
	std::string _textoMostrado; // Texto mostrado hasta ahora
	int _letraActual = 0;   // �ndice del car�cter que estamos mostrando actualmente
	//bool _completa = false; // Para saber si se termino de mostrar toda la historia
	//bool bandera = false;

};

