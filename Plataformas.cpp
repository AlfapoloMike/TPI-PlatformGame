#include "Plataformas.h"

Plataformas::Plataformas(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world, CollisionCategory category)
{

	////// ACA ESTAMOS DECLARANDO EL OBJETO CON SUS DEFINICIOES DE BOX2D
	setPositionPlataforma(newPosition);
	setBodyInWorld(world);
	setSizeBody(newSize);
	setFixture(category);

	/////  ACA ESTOY DECLARANDO LOS VALORES DE LA TEXTURA RECTANGULO DE SFML
	printRectangle(newSize);
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

}

void Plataformas::setSizeBody(sf::Vector2f newSize)
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_bodyBox.SetAsBox(newSize.x, newSize.y);
}

void Plataformas::setFixture(CollisionCategory category)
{
	////// SETEAMOS LA DENSIDAD PARA QUE SEA ESTATICA
	b2FixtureDef _fixtureDef;
	_fixtureDef.shape = &_bodyBox;
	_fixtureDef.friction = 0.5f;
	_fixtureDef.density = 0.0f;

	_fixtureDef.filter.categoryBits = WALL; // Categoría del muro
	_fixtureDef.filter.maskBits = PLAYER | ENEMY;   // Colisiona solo con el personaje


	_fixture=_body->CreateFixture(&_fixtureDef);
}

void Plataformas::getPositionBody()
{
	std::cout << "Plataforma creada en la posición: (" << _body->GetPosition().x << ", " << _body->GetPosition().y << ")" << std::endl;
	/////// ESTO SE PODRIA USAR PARA VERIFICAR LA COLISION? A REVISAR...

}
///PRUEBA PARA VER AL OBJETO FISICO
void Plataformas::printRectangle(sf::Vector2f newSize)
{
	
	//////// VINCULAMOS EL OBJETO DE BOX2D Y EL SHAPE DE SFML USANDO LA POSICION ACTUAL DEL OBJETO EN BOX2D

	_shape.setSize(sf::Vector2f((newSize.x*40*2),(newSize.y*40*2)));
	_shape.setOrigin(sf::Vector2f(_shape.getSize().x / 2, _shape.getSize().y / 2));
	_shape.setPosition(sf::Vector2f(_body->GetPosition().x*40,600- _body->GetPosition().y*40));
	_shape.setFillColor(sf::Color(255, 0, 0, 128));
}

sf::RectangleShape Plataformas::getShape()
{
	return _shape;
}

void Plataformas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);

}

sf::FloatRect Plataformas::getBounds() const
{
	return _shape.getGlobalBounds();
}

Plataformas::Plataformas()
{
}

Plataformas::~Plataformas()
{
}
