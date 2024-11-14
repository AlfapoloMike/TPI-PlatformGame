#pragma once
#include "Enemigo.h"
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Animation.h"
#include "CollisionCategories.h"

enum STATES {
	RUN_R, RUN_L, HIT, BUNNY_IDLE
};

class Conejo : public Enemigo {

	/********************/
public:
	Conejo(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float limiteIzq, float limiteDer, float pixelMetro);
	void moveEnemy();
	void setContact(bool state);
	void setPositionBody(sf::Vector2f newPosition);
	void setNewPosition(b2Vec2 newPosition);
	void setBodyInWorld(b2World& world);
	void setSizeBody(sf::Vector2f newSize);
	void setFixture();
	b2Vec2 getPositionBody();
	void setNewDirection(bool lado);
	void updateEnemie(int row, float deltaTime) override;
	void SetTextureRectAnimated();
	void setAnimationState();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setBorderWalk(float izquierdo, float derecho);



	void recibeDanio();

	~Conejo();

	//// Box2D GENERACION
private:
	b2BodyDef _bodyDef;
	b2Body* _body;
	b2PolygonShape _bodyBox;
	b2Fixture* _fixture;
	float _velocidad = 0.0f;
	/// en principio los limites tienen que ser el ancho de pantalla
	// al tocar la plataforma donde aparece, los limites se re-setean
	float _limiteIzq=0.0f, _limiteDer=20.0f;
	STATES _estado = STATES::RUN_R;
	b2Vec2 _positionBody;
	sf::Vector2f _sizeBody;
	bool _contacting = false;
	/********************/


};

