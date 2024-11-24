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
    void setFilterDataPlayer(bool state);
    void setInWall(bool state);

    // Getters
    sf::Sprite& getDraw();
    sf::Texture getTexture();
    b2Vec2 getPosition();
    bool* getVida();
    bool getFloorContact();

    bool getWallContact();

    ///gameplay

    void recibeDanio(int lado);

    void rebote();

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
        CAMINAR,
        DOBLE_SALTO,
        IN_WALL,
        HITTED_CD
    };
    ESTADOS _estado;

    int _saltos=0;
    Animation _animation;
    float hittedCdCounter = 0;
    float prevPos;
    float animationTimer = 0;
    bool floorContacting = false;
    bool roofContacting = false;
    bool vidas[4]{true, true, true, true};
    CollisionCategory _lastEnemyContact;
    uint16_t _maskBits = CollisionCategory::BUNNY | CollisionCategory::FRUITS | CollisionCategory::SKULLS | CollisionCategory::TURTLE | CollisionCategory::FATBIRD;
    bool hittedCd = false;

};