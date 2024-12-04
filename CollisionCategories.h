#pragma once
#include <cstdint>

enum CollisionCategory : uint16_t {
    PLAYER = 0x0002,
    WALL = 0x0004,
    BUNNY = 0x0008,
    FRUITS = 0x0010,
    SKULLS = 0x0020,
    PLATFORM = 0x0040,
    TURTLE = 0x0080,
    FATBIRD = 0x0100,
    RINO = 0x0200,
    LASER = 0x0400,
    CRYSTAL = 0x0800,
    ICEBALL = 0x1000,
    TOTTEMS = 0x2000,
    MAGE = 0x4000,
    PORTAL = 0x8000,
    /*
    A = 0x0080,
    B = 0x0100,
    C = 0x0200,
    D = 0x0400,
    E = 0x0800,
    F = 0x1000,
    G = 0x2000,
    H = 0x4000,
    I = 0x8000,
    */
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