#include "Plataformas.h"

Plataformas::Plataformas(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, bool tipo)
{

	////// ACA ESTAMOS DECLARANDO EL OBJETO CON SUS DEFINICIOES DE BOX2D
	setPositionPlataforma(newPosition);
	setBodyInWorld(world);
	setSizeBody(newSize);
	setFixture(tipo);
	setBordes(newPosition, newSize);
	/////  ACA ESTOY DECLARANDO LOS VALORES DE LA TEXTURA RECTANGULO DE SFML
	printRectangle(newPosition, newSize);
}


void Plataformas::setPositionPlataforma(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DE LA PLATAFORMA
	_bodyDef.type = b2_staticBody;
	_bodyDef.position.Set(newPosition.x,newPosition.y);
}

void Plataformas::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_body = world.CreateBody(&_bodyDef);
	/////////asgina a travez de un puntero el objeto plataforma al userData
	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

}

void Plataformas::setSizeBody(sf::Vector2f newSize)
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(newSize.x, newSize.y);
}

void Plataformas::setFixture(bool tipo)
{
	////// SETEAMOS LA DENSIDAD PARA QUE SEA ESTATICA

	if (tipo == true) {
		b2FixtureDef _fixtureDef;
		_fixtureDef.shape = &_bodyBox;
		_fixtureDef.friction = 0.5f;
		_fixtureDef.density = 0.0f;
		_fixtureDef.restitution = 0.0f;

		_fixtureDef.filter.categoryBits = PLATFORM; // Categoría del muro
		_fixtureDef.filter.maskBits = PLAYER | BUNNY | SKULLS | TURTLE | FATBIRD | RINO | CRYSTAL | TOTTEMS | MAGE;   // Colisiona solo con el personaje

	_fixture=_body->CreateFixture(&_fixtureDef);
	}
	else if (tipo == false) {
		b2FixtureDef _fixtureDef;
		_fixtureDef.shape = &_bodyBox;
		_fixtureDef.friction = 0.5f;
		_fixtureDef.density = 0.0f;
		_fixtureDef.restitution = 0.0f;

		_fixtureDef.filter.categoryBits = WALL; // Categoría del muro
		_fixtureDef.filter.maskBits = PLAYER | BUNNY | SKULLS | FRUITS | TURTLE | RINO | CRYSTAL | ICEBALL | TOTTEMS | MAGE;   // Colisiona solo con el personaje

		_fixture = _body->CreateFixture(&_fixtureDef);
	}


}

void Plataformas::getPositionBody()
{
	

}
void Plataformas::setBordes(sf::Vector2f newPosition, sf::Vector2f newSize)
{
	_bordeIzq = newPosition.x - (newSize.x);
	_bordeDer = newPosition.x + (newSize.x);

	std::cout << "Limite Izquierdo : " << _bordeIzq << " Limite derecho: " << _bordeDer << std::endl;


}

b2Vec2 Plataformas::getBorder() const
{
	b2Vec2 newBorder(_bordeIzq, _bordeDer);

	return newBorder;
}
///PRUEBA PARA VER AL OBJETO FISICO
void Plataformas::printRectangle(sf::Vector2f newPosition, sf::Vector2f newSize)
{
	
	//////// VINCULAMOS EL OBJETO DE BOX2D Y EL SHAPE DE SFML USANDO LA POSICION ACTUAL DEL OBJETO EN BOX2D

	_shape.setSize(sf::Vector2f((newSize.x*40*2),(newSize.y*40*2)));
	//_shape.setOrigin(sf::Vector2f(_shape.getSize().x / 2, _shape.getSize().y / 2));
	_shape.setOrigin(sf::Vector2f(newSize.x*40, newSize.y *40));
	//_shape.setPosition(sf::Vector2f(_body->GetPosition().x*40,600- _body->GetPosition().y*40));
	_shape.setPosition(sf::Vector2f(newPosition.x*40,600- newPosition.y*40));
	//_shape.setFillColor(sf::Color(255, 0, 0, 128));
	_shape.setFillColor(sf::Color(0, 0, 0, 0));

}

sf::RectangleShape Plataformas::getShape()
{
	return _shape;
}

void Plataformas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);

}



Plataformas::Plataformas()
{
}

Plataformas::~Plataformas()
{
}
