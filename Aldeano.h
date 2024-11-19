#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "CollisionCategories.h"

class Aldeano : public sf::Drawable {
public:
    Aldeano(sf::Vector2f newPosition, sf::Vector2f newVelocity, float pixelMetro);

    // Setters
    void setTexture(std::string texture);
    void setPosition(sf::Vector2f newPosition, float pixelMetro);
    void setSprite();
    void setVelocity(sf::Vector2f newVelocity);

    // Getters
    sf::Sprite getSprite();
    sf::Texture getTexture();
    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();

    virtual void updateVillager(int row, float deltaTime) = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ~Aldeano();

protected:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _position;
    sf::Vector2f _velocity;
    Animation _animation;
    sf::Vector2f _size;

};

