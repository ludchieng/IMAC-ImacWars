/*
 * Hippo.cpp
 */

#include "../includes/Hippo.hpp"

Hippo::Hippo(Player *player)
    : Unit(player, 100, 1, 2, 1, 65, 65) {
}

Hippo::Hippo(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Hippo::~Hippo() {
    
}