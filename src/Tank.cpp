/*
 * Tank.cpp
 */

#include "../includes/Tank.hpp"

Tank::Tank(int id, Player *player)
    : Unit(id, player, 100, 1, 2, 1, 65, 65) {
}

Tank::Tank(int id, Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(id, player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Tank::~Tank() {
    
}