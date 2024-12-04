#pragma once
#include <SFML/Graphics.hpp>
#include "MappingLevel.h"
#include "Animation.h"


enum class MAP_STATE {
	NORMAL,
	DISTORTION
};

class Map : public sf::Drawable {

protected:
	sf::Sprite _shape;
	sf::Texture _texture;
	sf::Texture _full;
	int _nivel = 0;
	Animation _animation;
	MAP_STATE _state = MAP_STATE::NORMAL;
	float animationTimer = 0;
	int _randomDelay = 0;

public:
	Map(int nivel);
	void setTexture(std::string texture);
	void SetTextureRectAnimated();
	void setAnimationState();
	void animationControl(float deltaTime);
	void update(int row, float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite getShape();

};






/*

funcion global guardar puntaje partida (char nombre, int puntaje)

	archivo = abrir archivo y guardarlo

	for(recorro el archivo){
		archivo = archivo[i]
		if(puntaje > archivo.puntaje){
	
			ponemos el puntero adelante del indice de archivo.puntaje
			y guardamos el nuevo valor

		}


	}




*/