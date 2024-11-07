#pragma once
#include <SFML/Graphics.hpp>
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include <iostream>
#include "Animation.h"

class Jugador : public sf::Drawable {
public:
    Jugador(b2World& world);
    void update(int row, float deltaTime);
    void cmd();
    void handleEvent(const sf::Event& event);
    void animationControl(float deltaTime);
    ~Jugador();

    // Setters
    void setTexture(std::string texture);
    void setPosition(sf::Vector2f newPosition);
    void SetTextureRectAnimated();
    void setAnimationState();

    // Getters
    sf::Sprite& getDraw();
    sf::Texture getTexture();
    b2Vec2 getPosition();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    b2BodyDef _bodyDef;
    b2Body* _body;
    b2PolygonShape _bodyBox;
    b2Fixture* _fixture;
    sf::Sprite _sprite;
    sf::Texture _texture;

    enum ESTADOS {
        AVANZA_DER,
        AVANZA_IZQ,
        SALTO_1,
        SALTO_2,
        QUIETO,
        CAE
    };
    ESTADOS _estado;

    int _saltos;
    Animation _animation;
    float _animationTimeCounter = 0;
    float prevPos;
    float animationJump = 0;
};
