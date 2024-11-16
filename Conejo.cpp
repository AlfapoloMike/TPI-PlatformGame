#include "Conejo.h"


Conejo::Conejo(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, sf::Vector2f newVelocity, float limiteIzq, float limiteDer, float pixelMetro):Enemigo(newPosition,newVelocity, pixelMetro)
{

	_estado = STATES::RUN_R;

	setPositionBody(newPosition);
	setBodyInWorld(world);
	setSizeBody(newSize);
	setFixture();
	_velocidad = 0.01f;
	setAnimationState();
	//_sprite.setOrigin(newSize.x * 40, newSize.y * 40);
	_sprite.setOrigin((float)_animation.getUvRect().width / 2, (float)_animation.getUvRect().height / 2);
	setPosition(sf::Vector2f(newPosition.x*pixelMetro, 600 - newPosition.y*pixelMetro));
	_sprite.setScale(-1, 1);
	_size = newSize;


}

void Conejo::setPositionBody(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DEL CUERPO
	_bodyDef.bullet = true;
	_bodyDef.position.Set(newPosition.x, newPosition.y);
	_bodyDef.type = b2_dynamicBody;
}

void Conejo::setNewPosition(b2Vec2 newPosition) {
	_positionBody = getPositionBody();
}

void Conejo::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);


	/////////asgina a travez de un puntero el objeto conejo al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
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
	_fixtureDef.friction = 0.3f;  // FRICCION
	_fixtureDef.restitution = 0.0f; // REBOTE , VALOR = 0 SIGNIFICA SIN REBOTE


	_fixtureDef.filter.categoryBits = BUNNY;
	_fixtureDef.filter.maskBits = WALL | PLAYER | PLATFORM;

	_fixture=_body->CreateFixture(&_fixtureDef);


}

b2Vec2 Conejo::getPositionBody()
{
	b2Vec2 position = _body->GetPosition();
	return position;
}

void Conejo::setNewDirection(bool lado) {
	///// SE GUARDA LA VELOCIDAD ACTUAL DE X E Y

	if (lado == true) {
		if (_velocidad < 0) {
			_velocidad = _velocidad * -1;
			_sprite.setScale(-1, 1);
			_estado = RUN_L;
			setAnimationState();
		}


	}else if (lado == false) {
		if (_velocidad > 0) {
			_velocidad = _velocidad * -1;
			_sprite.setScale(1, 1);
			_estado = RUN_R;
			setAnimationState();
			std::cout << " ENTRANDO ACA ACA ACA ACA ACA " << std::endl;
		}
	}

}

void Conejo::updateEnemie(int row, float deltaTime)
{


	Conejo::moveEnemy();
	//////// ANIMACION
	_sprite.setPosition(_positionBody.x * 40, 600 - _positionBody.y * 40);
	_sprite.setTextureRect(_animation.uvRect);
	_animation.Update(row, deltaTime);


}


void Conejo::moveEnemy()
{
	///// RECIBIMOS LA POSICION ACTUAL DEL CUERPO
	_positionBody = getPositionBody();
	

	// CAMBIA DE DIRECCION
	if (_positionBody.x <= _limiteIzq + _size.x && _estado == RUN_L) {
		_velocidad = 2; // Invertir la velocidad
		_sprite.setScale(-1,1);
		_estado = RUN_R;
		setAnimationState();
		std::cout << "Pasamos por la izquierda" << std::endl;
		_contacting = false;
	}else if (_positionBody.x >= _limiteDer - _size.x && _estado == RUN_R) {
		_velocidad = -2; // Invertir la velocidad
		_sprite.setScale(1,1);
		_estado = RUN_L;
		setAnimationState();
		std::cout << "Pasamos por la derecha" << std::endl;
		_contacting = false;
	}



	///// SE GUARDA LA VELOCIDAD ACTUAL DE X E Y
	b2Vec2 velocidadActual = _body->GetLinearVelocity();
	///// SE PASA LA VELOCIDAD DE Y ACTUAL, Y LA NUEVA VELOCIDAD DE X (_velocidad esta seteado como propiedad de clase)
	_body->SetLinearVelocity(b2Vec2(_velocidad, velocidadActual.y));

}


void Conejo::setContact(bool state) {
	_contacting = state;
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

	}
	if (_estado == BUNNY_IDLE) {
		setTexture("./assets/enemigos/Bunny/Idle_(34x44).png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.06f);
		_animation.setImageUvRectSize(&_texture);
	}

}

void Conejo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Conejo::setBorderWalk(float izquierdo, float derecho)
{
	_limiteIzq = izquierdo;
	_limiteDer = derecho;
	_velocidad = 2.0f;
}



void Conejo::recibeDanio()
{
	std::cout << "recibi daño, auch" << std::endl;
}


Conejo::~Conejo()
{
}
;