#pragma once
#include <SFML/Graphics.hpp>
#include "./packages/Box2D-static.2.4.1.1/build/native/include/box2d/box2d.h"
#include <iostream>
#include "CollisionCategories.h"
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
    void setSaltos();
    void setContactFloor(bool state);
    void setFilterDataPlayer(CollisionCategory newFilter, bool state);

    // Getters
    sf::Sprite& getDraw();
    sf::Texture getTexture();
    b2Vec2 getPosition();
    bool* getVida();

    ///gameplay

    void recibeDanio(int lado);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    b2BodyDef _bodyDef;
    b2Body* _body;
    b2PolygonShape _bodyBox;
    b2Fixture* _fixture;
    sf::Sprite _sprite;
    sf::Texture _texture;

    enum ESTADOS {
        SALTO,
        QUIETO,
        CAE,
        HITTED,
        CAMINAR
    };
    ESTADOS _estado;

    int _saltos=0;
    Animation _animation;
    float _animationTimeCounter = 0;
    float prevPos;
    float animationTimer = 0;
    bool floorContacting = false;
    bool vidas[4]{true, true, true, true};
};