#include "Jugador.h"

Jugador::Jugador(sf::Vector2f newPosition) {
	//_animationState = CAE;
	_corazones = 3;
	_estado = SALTO_DER;
	_velocidadSalto = 0.0f;
	setAnimationState();
	setPosition(newPosition);
}

void Jugador::setTexture(std::string texture) {
	_texture.loadFromFile(texture);
	_sprite.setTexture(_texture);
}

void Jugador::setPosition(sf::Vector2f newPosition) {
	_sprite.setPosition(sf::Vector2f(newPosition.x, newPosition.y));
}

void Jugador::setVelocidadSalto(float newVelocity) {
	_velocidadSalto = newVelocity;
}

sf::Sprite& Jugador::getDraw() {
	return _sprite;
}

sf::Texture Jugador::getTexture() {
	return _texture;
}

sf::Vector2f Jugador::getPosition() {
	return _posicion;
}

float Jugador::getVelocidadSalto() {
	return _velocidadSalto;
}

sf::Vector2f Jugador::getPrevPosition() {
	return _prevPosition;
}

void Jugador::update() {

	switch (_estado) {
	case QUIETO:
		break;

	case AVANZA_DER:
		mover(5, 0);
		_estado = ESTADOS::QUIETO;
		break;

	case AVANZA_IZQ:
		mover(-5, 0);
		_estado = ESTADOS::QUIETO;
		break;

	case SALTO_1:
		break;

	case SALTO_DER:
		mover(5, 0);  // Mover hacia adelante mientras salta
		break;

	case SALTO_IZQ:
		mover(-5, 0);  // Mover hacia atrás mientras salta
		break;
	}

	// Gravedad
	_velocidadSalto -= 2;
	mover(0, -_velocidadSalto);
}

void Jugador::cmd() {
	if (_estado == ESTADOS::QUIETO) {

		// Caminar hacia adelante
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			_estado = ESTADOS::AVANZA_DER;
		}

		// Caminar hacia atrás
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			_estado = ESTADOS::AVANZA_IZQ;
		}

		// Saltar recto
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			_estado = ESTADOS::SALTO_1;
			_velocidadSalto = 22;
		}

		// Saltar hacia adelante
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			&& (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
			_estado = ESTADOS::SALTO_DER;
			_velocidadSalto = 22;
		}

		// Saltar hacia atrás
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			&& (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
			_estado = ESTADOS::SALTO_IZQ;
			_velocidadSalto = 22;
		}
	}
}

void Jugador::quieto(float x, float y) {
	_estado = ESTADOS::QUIETO;
	_velocidadSalto = 0;
	_sprite.setPosition(x, y);
}


void Jugador::mover(float x, float y) {
	/// Limites laterales de nivel
	if (_sprite.getGlobalBounds().getPosition().x >= 712) {
		_sprite.setPosition(712, _sprite.getGlobalBounds().getPosition().y);
	}
	if (_sprite.getGlobalBounds().getPosition().x < 56) {
		_sprite.setPosition(56, _sprite.getGlobalBounds().getPosition().y);
	}
	_prevPosition = _sprite.getPosition();
	_sprite.move(x, y);
}

void Jugador::perderVelocidad() {
	_velocidadSalto = 0;
}

void Jugador::SetTextureRectAnimated() {
	_sprite.setTextureRect(_animation.uvRect);
}




void Jugador::setAnimationState() {

	if (_estado == ESTADOS::CAE) {
		//setTexture("./assets/personaje/Frogar/Fall(32x32).png");
		setTexture("./Fall_(32x32).png");
		_animation.setImageCount(sf::Vector2u(1, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}

	if (_estado == ESTADOS::QUIETO) {
		setTexture("./assets/personaje/Frogar/Idle(32x32).png");
		_animation.setImageCount(sf::Vector2u(11, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_estado == ESTADOS::AVANZA_DER) {
		setTexture("./assets/personaje/Frogar/Run(32x32).png");
		_animation.setImageCount(sf::Vector2u(12, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);

	}
	if (_estado == ESTADOS::AVANZA_IZQ) {
		setTexture("./assets/personaje/Frogar/Run(32x32).png"); /// Falta voltear
		_animation.setImageCount(sf::Vector2u(12, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);

	}
	if (_estado == ESTADOS::SALTO_DER) {
		setTexture("./assets/personaje/Frogar/Jump(32x32).png");
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}
	if (_estado == ESTADOS::SALTO_IZQ) {
		setTexture("./assets/personaje/Frogar/Jump(32x32).png"); /// Falta Voltear
		_animation.setImageCount(sf::Vector2u(8, 1));
		_animation.setSwitchTime(0.09f);
		_animation.setImageUvRectSize(&_texture);
	}

}

void Jugador::animationControl() {

	//if (_animationState == CAE) {
	if (_estado == CAE) {
		_animationTimeCounter += 0.01f;
		if (_animationTimeCounter >= 2.43) { // 2.43segs Termina IDLE y extiende espinas
			_estado = AVANZA_DER;
			_animationTimeCounter = 0;
			setAnimationState();
		}
	}
}

Jugador::~Jugador() {
}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);

}

sf::FloatRect Jugador::getBounds() const {
	return _sprite.getGlobalBounds();
}
