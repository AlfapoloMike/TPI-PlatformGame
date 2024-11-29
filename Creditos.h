#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Creditos : public sf::Drawable{

public:
	Creditos();
	~Creditos();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture _creditosTexture;
	sf::Sprite _creditosSprite;
	std::string _rutaImagen;

	sf::Font font;

	sf::Text _creditosTitulo;
	sf::Text _creditosTituloSombra;
	sf::Text _creditosText;

	std::string _creditos;

	sf::Music _creditosMusic;

};

