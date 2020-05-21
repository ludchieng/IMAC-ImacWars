/*
 * Bee.cpp
 */

#include "../includes/Bee.hpp"

Bee::Bee(Player *player)
    : Unit(player, 100, 2, 3, 2, 50, 30) {
}

Bee::Bee(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Bee::~Bee() {
    
}