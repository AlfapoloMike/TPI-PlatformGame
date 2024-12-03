#pragma once
#include "Aldeano.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"

enum class Rino_STATE {
	IDLE,
	RUN,
	HIT,
	HIT_WALL,
	IDLE_RESTORED
};

class Rino : public Aldeano {

public:

	Rino(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float pixelMetro);

	void setPositionBody(sf::Vector2f newPosition);
	void setBodyInWorld(b2World& world);
	void setSizeBody(sf::Vector2f newSize);
	void setFixture();
	b2Vec2 getPositionBody();

	//***************MOVIMIENTO, VELOCIDAD Y DIRECCION*******************************//

	void move(float velocidad);
	void recibeDanio();
	bool getSpikes();

	//***************SFML**************************/
	void SetTextureRectAnimated();
	void setAnimationState();
	void animationControl(float deltaTime);

	void setNewDirectionR();

	void setNewDirectionL();


	void updateVillager(int row, float deltaTime);
	void destroyBody(b2World& world);
	~Rino();

private:

	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	float _velocidad = 0.0f;
	/// en principio los limites tienen que ser el ancho de pantalla
	// al tocar la plataforma donde aparece, los limites se re-setean
	float _limiteIzq = 0.0f, _limiteDer = 20.0f;
	Rino_STATE _animationState = Rino_STATE::IDLE;
	b2Vec2 _positionBody;
	bool _directionR = false, _directionL=false;
	float _animationTimeCounter = 0;
	bool _dizzy = false;
	bool _alive = true;
};