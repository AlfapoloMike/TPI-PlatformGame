#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "Menu.h"



class Intro : public sf::Drawable {
public:
	Intro();
	~Intro();
	void update(bool &cambioEstado);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::Texture _introTexture;
	sf::Sprite _introSprite;
	std::string _rutaImagen;

	sf::Music _introMusic;


	float opacidad;

	bool fadeOn = true;
	bool musicOn = true;

};

