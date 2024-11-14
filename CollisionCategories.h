#pragma once
#include <cstdint>

enum CollisionCategory : uint16_t {
    PLAYER = 0x0002,
    WALL = 0x0004,
    ENEMY = 0x0008,
    FRUITS = 0x0010,
    SKULLS = 0x0020,
    PLATFORM = 0x0040,
    ////001
    ////010
    ////100
    ////111 and 001 = 001
    ////111 and 010 = 010
    ////111 and 100 = 100
    ////111 and 110 = 110
    ////110 and 010 = 010
    ////101 and 010 = 000
    ////100 and 010 = 000
    ////001 and 111 = 001
    ////011 and 111 = 011
    ////100 and 001 = 000

};