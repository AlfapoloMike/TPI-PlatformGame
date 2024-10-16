#pragma once
#include <SFML/Graphics.hpp>

enum ESTADOS_JUGADOR {
	CAMINANDO_ATRAS, CAMINANDO_ADELANTE, SALTANDO, QUIETO, DOBLE_SALTO, HERIDO, MUERTO
};


class Personaje : public sf::Drawable
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	/// Animation _animation;
	float _sizeX = 32.0f;
	float _sizeY = 32.0f;
	int _health = 3;
	ESTADOS_JUGADOR _estado;
	sf::Vector2f _velocity = sf::Vector2f(4.0f,0.0f);


public:

	Personaje();
	void personajeUpdate();
	sf::Sprite getDraw();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f NewPosition);
	~Personaje();


};
