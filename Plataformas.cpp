#include "Plataformas.h"


Plataformas::Plataformas(sf::Vector2f newPosition, sf::Vector2f newSize, b2World& world)
{

	////// ACA ESTAMOS DECLARANDO EL OBJETO CON SUS DEFINICIOES DE BOX2D
	setPositionPlataforma(newPosition);
	setBodyInWorld(world);
	setSizePlataforma(newSize);
	setDensity();

	/////  ACA ESTOY DECLARANDO LOS VALORES DE LA TEXTURA RECTANGULO DE SFML
	printRectangle(newSize);
}

void Plataformas::setPositionPlataforma(sf::Vector2f newPosition)
{
	///// DEFINIMOS LA POSICION DE LA PLATAFORMA
	_plataformaDef.position.Set(newPosition.x,newPosition.y);
}

void Plataformas::setBodyInWorld(b2World& world)
{
	////// SETEAMOS LA PLATAFORMA DENTRO DEL MUNDO CON UNA REFERENCIA
	_groundBody = world.CreateBody(&_plataformaDef);

}

void Plataformas::setSizePlataforma(sf::Vector2f newSize)
{
	/////// SETEAMOS EL CUERPO DE LA PLATAFORMA CON TAMAÑO
	_groundBox.SetAsBox(newSize.x, newSize.y);
}

void Plataformas::setDensity()
{
	////// SETEAMOS LA DENSIDAD PARA QUE SEA ESTATICA
	_groundBody->CreateFixture(&_groundBox, 0.0f);
}

void Plataformas::getPositionBody()
{
	std::cout << "Plataforma creada en la posición: (" << _groundBody->GetPosition().x << ", " << _groundBody->GetPosition().y << ")" << std::endl;
	/////// ESTO SE PODRIA USAR PARA VERIFICAR LA COLISION? A REVISAR...

}
///PRUEBA PARA VER AL OBJETO FISICO
void Plataformas::printRectangle(sf::Vector2f newSize)
{
	
	//////// VINCULAMOS EL OBJETO DE BOX2D Y EL SHAPE DE SFML USANDO LA POSICION ACTUAL DEL OBJETO EN BOX2D

	_shape.setSize(sf::Vector2f((newSize.x*40*2),(newSize.y*40*2)));
	_shape.setOrigin(sf::Vector2f(_shape.getSize().x / 2, _shape.getSize().y / 2));
	_shape.setPosition(sf::Vector2f(_groundBody->GetPosition().x*40,600-_groundBody->GetPosition().y*40));
	_shape.setFillColor(sf::Color::Red);
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
