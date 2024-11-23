#pragma once
#include <SFML/Graphics.hpp>
#include "MappingLevel.h"


class Map : public sf::Drawable {

protected:
	sf::Sprite _shape;
	sf::Texture _texture;
	int _nivel = 0;

public:
	Map(int nivel);
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