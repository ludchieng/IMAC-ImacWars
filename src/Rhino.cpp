/*
 * Rhino.cpp
 */

#include "../includes/Rhino.hpp"

Rhino::Rhino(Player *player)
    : Unit(player, 100, 1, 2, 1, 65, 65) {
}

Rhino::Rhino(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Rhino::~Rhino() {
    
}