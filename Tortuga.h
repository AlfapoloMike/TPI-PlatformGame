#pragma once
#include "Aldeano.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"

class Tortuga : public Aldeano {

public:
	Tortuga(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float pixelMetro);


	//***************BOX2D****************************/
	void setPositionBody(sf::Vector2f newPosition);
	void setBodyInWorld(b2World& world);
	void setSizeBody(sf::Vector2f newSize);
	void setFixture();
	b2Vec2 getPositionBody();

	//***************MOVIMIENTO, VELOCIDAD Y DIRECCION*******************************//

	void setNewDirection(bool lado);
	void setContact(bool state);
	void setBorderWalk(float izquierdo, float derecho);
	void move(float velocidad);
	void recibeDanio();
	bool getSpikes();

	//***************SFML**************************/
	void SetTextureRectAnimated();
	void setAnimationState();
	void animationControl(float deltaTime);

	//***************UPDATE Y DRAW****************************/

	void updateVillager(int row, float deltaTime) override;
	void destroyBody(b2World& world);
	~Tortuga();

private:
	enum AnimationState {
		ESPINAS_EXT,
		ESPINAS_RET,
		ESPINAS_IDLE,
		IDLE,
		HITTED
	};

	/********************/
	//// Box2D GENERACION

	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	float _velocidad = 0.0f;
	/// en principio los limites tienen que ser el ancho de pantalla
	// al tocar la plataforma donde aparece, los limites se re-setean
	float _limiteIzq = 0.0f, _limiteDer = 20.0f;
	AnimationState _animationState = IDLE;
	b2Vec2 _positionBody;
	bool _contacting = false;
	float _animationTimeCounter = 0;
	bool _spikes = false;
	bool _alive = true;
};

