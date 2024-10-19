#include "Skull.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Skull::Skull(std::string texture, sf::Vector2f newPosition, sf::Vector2f newVelocity):Enemigo(texture,newPosition, newVelocity)
{

}

void Skull::updateSkull()
{
	_sprite.move(_velocity.x, _velocity.y);


}

void Skull::move()
{
}

