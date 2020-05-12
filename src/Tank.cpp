/*
 * Tank.cpp
 */

#include "../includes/Tank.hpp"

Tank::Tank(Player *player)
    : Unit(player, 100, 1, 2, 1, 65, 65) {
}

Tank::Tank(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Tank::~Tank() {
    
}