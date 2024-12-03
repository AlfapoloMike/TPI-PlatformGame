#pragma once
#include <SFML/Graphics.hpp>

class Ayuda : public sf::Drawable{

public:
	Ayuda();
	~Ayuda();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::Font font;
	// Fondo
	sf::Texture _ayudaTexture;
	sf::Sprite _ayudaSprite;
	// Titulo
	sf::Text _instruccionesTitulo;
	sf::Text _instruccionesTituloSombra;

	sf::Text _controles;
	sf::Text _objetivo;
	std::string objetivo;
	std::string controles;
};

