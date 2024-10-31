#include "Conejo.h"

Conejo::Conejo(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float limiteIzq, float limiteDer, float pixelMetro):Enemigo(newPosition,newVelocity, pixelMetro)
{
	_limiteIzq = limiteIzq;
	_limiteDer = limiteDer;
	setPositionBody(newPosition);
	setBodyInWorld(world);
	setSizeBody(newSize);
	setFixture();
	_estado = STATES::RUN_R;
	setAnimationState();
	setPosition(sf::Vector2f(newPosition.x*pixelMetro, 600 - newPosition.y*pixelMetro));
	_sprite.setScale(-1, 1);

}

void Conejo::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DE LA PLATAFORMA
	_bodyDef.position.Set(newPosition.x, newPosition.y);
	_bodyDef.type = b2_dynamicBody;
}

void Conejo::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);
}

void Conejo::setSizeBody(sf::Vector2f newSize)
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(newSize.x, newSize.y);
}

void Conejo::setFixture()
{
	b2FixtureDef _fixtureDef;

	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 1.0f;   // DENSISDAD
	_fixtureDef.friction = 0.8f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE
	_fixture=_body->CreateFixture(&_fixtureDef);


}

b2Vec2 Conejo::getPositionBody()
{
	b2Vec2 position = _body->GetPosition();
	return position;
}

void Conejo::updateEnemie(int row, float deltaTime)
{
	float posX = _body->GetPosition().x;

	// CAMBIA DE DIRECCION
	// SE PODRIA IMPLEMENTAR DE ALGUNA FORMA CON BOX2D O
	// UNA FORMA DINAMICA DE ENCONTRAR EL ANCHO DE CADA PLATAFORMA DONDE ESTA PARADO

	if (posX <= _limiteIzq || posX >= _limiteDer) {
		_velocidad = _velocidad * -1; // Invertir la velocidad
		_sprite.setScale(_sprite.getScale().x*-1,_sprite.getScale().y);

	}

	//////// ANIMACION

	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.getUvRect().width / 2.0, _animation.getUvRect().height / 2.0);
	_animation.Update(row, deltaTime);


	///// RECIBIMOS LA POSICION ACTUAL DEL CUERPO
	b2Vec2 positionRabbit = getPositionBody();

	///// SE POSICIONA EL SPRITE EN EL CUERPO
	///// MEJORAR EL TRASPASO DE DATOS DE 40 = PIXEL METRO Y 600 = ALTO DE PANTALLA
	_sprite.setPosition(positionRabbit.x * 40, 600 - positionRabbit.y * 40);

	/// MOVIMIENTO
	Conejo::moveEnemy();
}


void Conejo::moveEnemy()
{
	
	///// SE GUARDA LA VELOCIDAD ACTUAL DE X E Y
	b2Vec2 velocidadActual = _body->GetLinearVelocity();
	///// SE PASA LA VELOCIDAD DE Y ACTUAL, Y LA NUEVA VELOCIDAD DE X (_velocidad esta seteado como propiedad de clase)
	_body->SetLinearVelocity(b2Vec2(_velocidad, velocidadActual.y));

}


/////////////////// GRAPHICS


void setAnimation() {

}

void Conejo::SetTextureRectAnimated() {
	///// SE SETEA EL RECTANGULO QUE CORRESPONDE SOLO A LA PARTE
	///// QUE QUEREMOS VER DE LA TEXTURA, YA QUE LA TEXTURA ES UN CONJUNTO DE FRAMES
	_sprite.setTextureRect(_animation.uvRect);

}

void Conejo::setAnimationState()
{

	//////// SEGUN EL ESTADO SETEAMOS LA ANIMACION Y SUS PARAMETROS.
	if (_estado == RUN_R || _estado == RUN_L) {
		setTexture("./assets/enemigos/Bunny/Run_(34x44).png");
		_animation.setImageCount(sf::Vector2u(12, 1));
		_animation.setSwitchTime(0.06f);
		_animation.setImageUvRectSize(&_texture);
		_sprite.setOrigin(_animation.getUvRect().width / 2.0, _animation.getUvRect().height / 2.0);

	}

}

void Conejo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}


Conejo::~Conejo()
{
}
;