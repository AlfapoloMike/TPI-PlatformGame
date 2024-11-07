#include "Jugador.h"

const float SCALE = 40.0f; // Actualizamos el valor de SCALE a 40

Jugador::Jugador(b2World& world) {
    _bodyDef.type = b2_dynamicBody;
    _bodyDef.position.Set(2.50f, 7.0f); // Posición inicial en metros
    _bodyDef.linearDamping = 0.5f;
    _body = world.CreateBody(&_bodyDef);

    _bodyBox.SetAsBox(0.35f, 0.35f); // Tamaño en metros (1 metro de ancho y alto)
    b2FixtureDef _fixtureDef;
    _fixtureDef.shape = &_bodyBox;
    _fixtureDef.density = 1.0f; // Mantén la densidad para colisiones
    _fixtureDef.friction = 0.3f;
    _fixtureDef.restitution = 0.0f; // Sin rebote
    _fixtureDef.filter.categoryBits = PLAYER; // Categoría del muro
    _fixtureDef.filter.maskBits = WALL;   // Colisiona solo con el personaje
    _fixture = _body->CreateFixture(&_fixtureDef);

    // Ajustar el origen al centro del personaje (en relación con el nuevo SCALE)
    _sprite.setOrigin(16, 16);
    _estado = QUIETO;
    _saltos = 0;
    setAnimationState();


}

void Jugador::update(int row, float deltaTime) {
    // Obtener posición de Box2D y adaptarla con el nuevo SCALE
    b2Vec2 pos = _body->GetPosition();
    _sprite.setPosition(pos.x * SCALE, 600.0f - (pos.y * SCALE));
    cmd();
    animationControl(deltaTime);
    _sprite.setTextureRect(_animation.uvRect);
    _sprite.setOrigin(_animation.getUvRect().width / 2.f, _animation.getUvRect().height / 2.f);
    _animation.Update(0, deltaTime);
}

void Jugador::cmd() {
    b2Vec2 velocity = _body->GetLinearVelocity();

    // Movimiento horizontal
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x = 2.0f; /// DERECHA
        _estado = AVANZA_DER;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -2.0f; /// IZQUIERDA
        _estado = AVANZA_IZQ;
    }
    else {
        velocity.x = 0; /// QUIETO
        _estado = QUIETO;
    }

    // Salto y doble salto
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        && velocity.y <= 0.01f
        && _saltos < 2) {
        velocity.y = 6.5; // AJUSTA EL SALTO
        _estado = SALTO_1;
        _saltos++;
        std::cout << "Salto: " << _saltos << std::endl;
    }

    /// REINICIO CONTADOR DE SALTOS
    if (std::abs(velocity.y) < 0.01f && _body->GetContactList() != nullptr) {
        _saltos = 0;
        std::cout << "Salto: " << _saltos << std::endl;
    }

    _body->SetLinearVelocity(velocity);

    // Debugging info
    //std::cout << "PosX SPRITE: " << _sprite.getPosition().x << std::endl;
    //std::cout << "PosY SPRITE: " << _sprite.getPosition().y << std::endl;
    //std::cout << "PosX BODY: " << _body->GetPosition().x << std::endl;
    //std::cout << "PosY BODY: " << _body->GetPosition().y << std::endl;
    //std::cout << "Saltos: " << _saltos << std::endl;
}

void Jugador::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            _estado = AVANZA_DER;
            setAnimationState();
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            _estado = AVANZA_IZQ;
            setAnimationState();
            break;
        case sf::Keyboard::Space:
            if (_saltos == 0) {
                _estado = SALTO_1;
            }
            else if (_saltos == 1) {
                _estado = SALTO_2;
            }
            setAnimationState();
            break;
        default:
            break;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        if ((event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) && _estado == AVANZA_DER) {
            _estado = QUIETO;
            setAnimationState();
        }
        else if ((event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) && _estado == AVANZA_IZQ) {
            _estado = QUIETO;
            setAnimationState();
        }
    }
}

void Jugador::animationControl(float deltaTime) {
    if (_saltos == 2) {
        animationJump += deltaTime;
        if (animationJump > 1.5f) {
            _estado = CAE;
            animationJump = 0;
            setAnimationState();
        }
    }
}


/*void Personaje::animationControl() {
    //if (_animationState == CAE) {
    if (_estado == QUIETO) {
        _animationTimeCounter += 0.01f;
        if (_animationTimeCounter >= 2.43) { // 2.43segs Termina IDLE y extiende espinas
            _estado = AVANZA_DER;
            _animationTimeCounter = 0;
            setAnimationState();
        }
    }
}*/

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
    else if (_estado == ESTADOS::QUIETO) {
        setTexture("./assets/personaje/Frogar/Idle(32x32).png");
        _animation.setImageCount(sf::Vector2u(11, 1));
        _animation.setSwitchTime(0.06f);
        _animation.setImageUvRectSize(&_texture);
    }
    else if (_estado == ESTADOS::AVANZA_DER) {
        setTexture("./assets/personaje/Frogar/Run(32x32).png");
        _animation.setImageCount(sf::Vector2u(12, 1));
        _animation.setSwitchTime(0.09f);
        _sprite.setScale(1.f, 1.f);  // Voltear para que mire a la DERECHA
        _animation.setImageUvRectSize(&_texture);
    }
    else if (_estado == ESTADOS::AVANZA_IZQ) {
        setTexture("./assets/personaje/Frogar/Run(32x32).png");
        _animation.setImageCount(sf::Vector2u(12, 1));
        _animation.setSwitchTime(0.09f);
        _sprite.setScale(-1.f, 1.f);  // Voltear para que mire a la IZQUIERDA
        _animation.setImageUvRectSize(&_texture);
    }
    if (_estado == ESTADOS::SALTO_1) {
        setTexture("./assets/personaje/Frogar/Jump(32x32).png");
        _animation.setImageCount(sf::Vector2u(1, 1));
        _animation.setSwitchTime(0.09f);
        _animation.setImageUvRectSize(&_texture);
    }
    /*if (_estado == ESTADOS::SALTO_2) {
        setTexture("./assets/personaje/Frogar/DoubleJump(32x32).png");
        _animation.setImageCount(sf::Vector2u(6, 1));
        _animation.setSwitchTime(0.01f);
        _animation.setImageUvRectSize(&_texture);
    }
    if (_estado == ESTADOS::SALTO_IZQ) {
        setTexture("./assets/personaje/Frogar/Jump(32x32).png"); /// Falta Voltear
        _animation.setImageCount(sf::Vector2u(8, 1));
        _animation.setSwitchTime(0.09f);
        _animation.setImageUvRectSize(&_texture);
    }*/

}


void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

Jugador::~Jugador() {
    // Destrucción del cuerpo físico se maneja automáticamente por Box2D
}






