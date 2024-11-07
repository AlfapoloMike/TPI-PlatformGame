#pragma once
#include <cstdint>

enum CollisionCategory : uint16_t {
    PLAYER = 0x0001,
    WALL = 0x0002,
    ENEMY = 0x0004,
};