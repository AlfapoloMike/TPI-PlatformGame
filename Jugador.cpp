#include "Jugador.h"

const float SCALE = 40.0f; // Actualizamos el valor de SCALE a 40

Jugador::Jugador(b2World& world) {
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.position.Set(8.50f, 19.0f); // Posición inicial en metros

	_body = world.CreateBody(&_bodyDef);

	/////////asgina a travez de un puntero el objeto Jugador al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

	_bodyBox.SetAsBox(0.4f, 0.4f); // Tamaño en metros (1 metro de ancho y alto)
	b2FixtureDef _fixtureDef;
	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.density = 1.0f; // Mantén la densidad para colisiones
	_fixtureDef.friction = 0.3f;
	_fixtureDef.restitution = 0.0f; // Sin rebote
	_fixtureDef.filter.categoryBits = PLAYER; // Categoría del muro
	_fixtureDef.filter.maskBits = WALL | BUNNY | FRUITS | PLATFORM | SKULLS | TURTLE;   // Colisiona solo con el personaje
		
	_fixture = _body->CreateFixture(&_fixtureDef);

	// Ajustar el origen al centro del personaje (en relación con el nuevo SCALE)
	_estado = QUIETO;
	setAnimationState();
	_sprite.setOrigin(0.4f*40, 0.4f * 40);
	_sprite.setPosition(2.50f * 40, 600 - 7.0f * 40);
	_saltos = 0;


}



void Jugador::update(int row, float deltaTime) {
	// Obtener posición de Box2D y adaptarla con el nuevo SCALE
	b2Vec2 pos = _body->GetPosition();
	b2Vec2 velocity = _body->GetLinearVelocity();

	if (velocity.y > 0 && floorContacting == false) {
		
		setFilterDataPlayer(PLATFORM, false);
	}
	else if (velocity.y < 0) {
		setFilterDataPlayer(PLATFORM, true);

	}


	_sprite.setPosition(pos.x * SCALE, 600.0f - (pos.y * SCALE));
	cmd();
	animationControl(deltaTime);
	_sprite.setTextureRect(_animation.uvRect);
	_animation.Update(0, deltaTime);
}

void Jugador::cmd() {

	b2Vec2 velocity = _body->GetLinearVelocity();


	if (_estado != HITTED) {
		// Movimiento horizontal
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			velocity.x = 3.0f; /// DERECHA
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			velocity.x = -3.0f; /// IZQUIERDA
		}
		else {
			velocity.x = 0; /// QUIETO
		}

		// Salto y doble salto
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			&& velocity.y <= 0.01f
			&& _saltos < 2) {


			velocity.y = 5.6;

			_saltos++;

		}
	}


	_body->SetLinearVelocity(velocity);


}


void Jugador::animationControl(float deltaTime) {

	b2Vec2 velocity = _body->GetLinearVelocity();


	if (_estado == HITTED && hittedCd == false) {
		animationTimer += deltaTime;
		if (animationTimer >= 1.3f) {
			_estado = CAE;
			setAnimationState();
			animationTimer = 0;
			hittedCd = true;
			//setFilterDataPlayer(true);
		}
	}
	if (hittedCd == true) {
		hittedCdCounter += deltaTime;
		_sprite.setColor(sf::Color(255, 255, 255, 128));
		if (hittedCdCounter >= 1.5f) {
			_sprite.setColor(sf::Color::White);
			hittedCd = false;
			hittedCdCounter = 0;
			setFilterDataPlayer(true);

		}
	}

	if (floorContacting == true && _estado == CAE) {
		_estado = QUIETO;
		setAnimationState();
	}


	if (_estado == QUIETO) {
		if (velocity.x > 0 && velocity.y <= 0.01f) {
			_estado = CAMINAR;
			setAnimationState();
			_sprite.setScale(-1, 1);
		}
		else if (velocity.x < 0 && velocity.y <= 0.01f) {
			_estado = CAMINAR;
			setAnimationState();
			_sprite.setScale(1, 1);
		}
		else if (velocity.y > 0.01f) {
			_estado = SALTO;
			setAnimationState();
		}


	}
	if (_estado == CAMINAR) {
		if (velocity.x > 0) {
			_sprite.setScale(1, 1);
		}
		else if (velocity.x < 0) {
			_sprite.setScale(-1, 1);
		}
		if (velocity.x == 0) {
			_estado = QUIETO;
			setAnimationState();
		}
		else if (velocity.y > 0.01f) {
			_estado = SALTO;
			setAnimationState();
		}
	}
	if (_estado == SALTO) {


		if (velocity.x > 0) {
			_sprite.setScale(1, 1);
		}
		else if (velocity.x < 0) {
			_sprite.setScale(-1, 1);
		}
		if (velocity.y <= 0.01f) {
			_estado = CAE;
			setAnimationState();

			if (_saltos == 2) {
				_estado = DOBLE_SALTO;
				setAnimationState();
			}
		}
		else if (velocity.y >= 0.01 && _saltos == 2) {
			_estado = DOBLE_SALTO;
			setAnimationState();
		}

	}
	if (_estado == DOBLE_SALTO) {
		animationTimer += deltaTime;
		if (animationTimer >= 0.3f) {
			if (velocity.y >= 0.01f) {
				_estado = SALTO;
				setAnimationState();
				animationTimer = 0;
				_saltos++;

			}
			else if (velocity.y <= 0.01f) {
				_estado = CAE;
				setAnimationState();
				animationTimer = 0;
				_saltos++;

			}
		}
	}
	if (_estado == CAE) {

		if (velocity.x > 0) {
			_sprite.setScale(1, 1);
		}
		else if (velocity.x < 0) {
			_sprite.setScale(-1, 1);
		}
		if (_saltos == 2) {
			_estado = DOBLE_SALTO;
			setAnimationState();
			animationTimer = 0;
		}
	}





}


/// GETTERS
sf::Sprite& Jugador::getDraw() {
	return _sprite;
}

sf::Texture Jugador::getTexture() {
	return _texture;
}

b2Vec2 Jugador::getPosition() {
	return _body->GetPosition();
}

bool* Jugador::getVida()
{
	return vidas;
}

bool Jugador::getFloorContact()
{
	return floorContacting;
}

bool Jugador::getWallContact() {
	return roofContacting;
}


/// SETTERS
void Jugador::setTexture(std::string texture) {
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Jugador::setPosition(sf::Vector2f newPosition) {
	_sprite.setPosition(sf::Vector2f(newPosition.x, newPosition.y));
}

void Jugador::SetTextureRectAnimated() {
	_sprite.setTextureRect(_animation.uvRect);
}

void Jugador::setAnimationState() {
	if (_estado == ESTADOS::CAE) {
		setTexture("./assets/personaje/Frogar/Fall(32x32).png");
		_animation.setImageCount(sf::Vector2u(1, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_estado == ESTADOS::QUIETO) {
		setTexture("./assets/personaje/Frogar/Idle(32x32).png");
		_animation.setImageCount(sf::Vector2u(11, 1));
		_animation.setSwitchTime(0.06f);
		_animation.setImageUvRectSize(&_texture);
		
	}
	if (_estado == ESTADOS::SALTO) {
		setTexture("./assets/personaje/Frogar/Jump(32x32).png");
		_animation.setImageCount(sf::Vector2u(1, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_estado == ESTADOS::CAMINAR) {
		setTexture("./assets/personaje/Frogar/Run(32x32).png");
		_animation.setImageCount(sf::Vector2u(12, 1));
		_animation.setSwitchTime(0.07f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_estado == ESTADOS::DOBLE_SALTO) {
		setTexture("./assets/personaje/Frogar/DoubleJump(32x32).png");
		_animation.setImageCount(sf::Vector2u(6, 1));
		_animation.setSwitchTime(0.02f);
		_animation.setImageUvRectSize(&_texture);
	}

	if (_estado == ESTADOS::HITTED) {
		setTexture("./assets/personaje/Frogar/Hit(32x32).png");
		_animation.setImageCount(sf::Vector2u(7, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_estado == ESTADOS::IN_WALL) {
		setTexture("./assets/personaje/Frogar/WallJump(32x32).png");
		_animation.setImageCount(sf::Vector2u(5, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}


}

void Jugador::setSaltos()
{
	_saltos = 0;
}

void Jugador::setContactFloor(bool state)
{
	floorContacting = state;
}

void Jugador::setFilterDataPlayer(CollisionCategory newFilter, bool state)
{

	//////// ENCENDEMOS UN FILTRO DE CONTACTO 
	if (state == true) {

		b2Filter filtro = _body->GetFixtureList()->GetFilterData();
		filtro.maskBits |= newFilter;
		_body->GetFixtureList()->SetFilterData(filtro);
	}
	//////// APAGAMOS UN FILTRO DE CONTACTO
	else if (state == false) {
		b2Filter filtro = _body->GetFixtureList()->GetFilterData();
		filtro.maskBits &= ~newFilter;
		_body->GetFixtureList()->SetFilterData(filtro);

	}

}
void Jugador::setFilterDataPlayer(bool state) {

	if (state == true) {

		b2Filter filtro = _body->GetFixtureList()->GetFilterData();
		filtro.maskBits |= _maskBits;
		_body->GetFixtureList()->SetFilterData(filtro);
	}
	//////// APAGAMOS UN FILTRO DE CONTACTO
	else if (state == false) {
		b2Filter filtro = _body->GetFixtureList()->GetFilterData();
		filtro.maskBits &= ~_maskBits;
		_body->GetFixtureList()->SetFilterData(filtro);
	}

}

void Jugador::setInWall(bool state)
{
	if (state == true && _estado != HITTED) {
		_estado = IN_WALL;
		roofContacting = true;
		setAnimationState();
	}
	else if (state == false && _estado != HITTED) {
		roofContacting = false;
		_estado = CAE;
		setAnimationState();
	}

}


void Jugador::recibeDanio(int lado)
{
	if (hittedCd == false) {
		if (_estado != HITTED) {

			if (vidas[3] == true) {

				vidas[3] = false;

				_estado = HITTED;
				setAnimationState();


			}
			else if (vidas[2] == true) {

				vidas[2] = false;

				_estado = HITTED;
				setAnimationState();


			}
			else if (vidas[1] == true) {

				vidas[1] = false;

				_estado = HITTED;
				setAnimationState();

			}
			else if (vidas[0] == true) {

				vidas[0] = false;


				_estado = HITTED;
				setAnimationState();


				std::cout << "Perdiste" << std::endl;

			}
			else if (vidas[0] == false) {
				std::cout << "Estas muertisimo" << std::endl;


				_estado = HITTED;
				setAnimationState();


			}

		}

	}


}

void Jugador::rebote() {

	b2Vec2 velocity = _body->GetLinearVelocity();

	velocity.y = 5.0f;

	_body->SetLinearVelocity(velocity);
}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_sprite, states);
}

Jugador::~Jugador() {
	// Destrucción del cuerpo físico se maneja automáticamente por Box2D
}






