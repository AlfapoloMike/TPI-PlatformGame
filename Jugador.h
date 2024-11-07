#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collisionable.h"

class Jugador : public sf::Drawable, public Collisionable {

public:
	Jugador(sf::Vector2f newPosition);

	// Setters
	void setTexture(std::string texture);
	void setPosition(sf::Vector2f newPosition);
	void setVelocidadSalto(float newVelocity);
	void SetTextureRectAnimated();
	void setAnimationState();

	// Getters
	sf::Sprite& getDraw();
	sf::Texture getTexture();
	sf::Vector2f getPosition();
	float getVelocidadSalto();
	sf::Vector2f getPrevPosition();

	//void saltar();
	//void recolectarFruta();
	void update();
	void cmd();
	void quieto(float x, float y);
	void mover(float x, float y);
	void perderVelocidad();

	void animationControl();
	//void rescatarAldeano();
	//void recibirDanio();
	//void avanzarPortal();
	~Jugador();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::FloatRect getBounds() const override;

private:

	enum ESTADOS {
		AVANZA_DER,
		AVANZA_IZQ,
		SALTO_1,
		SALTO_2,
		SALTO_DER,
		SALTO_IZQ,
		QUIETO,
		CAE
	};

	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _prevPosition;
	sf::Vector2f _posicion;
	int _corazones;
	float _velocidadSalto;
	ESTADOS _estado;	
	Animation _animation;
	//ESTADOS _animationState;
	float _animationTimeCounter = 0;

};

