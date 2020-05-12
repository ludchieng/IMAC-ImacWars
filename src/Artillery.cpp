/*
 * Artillery.cpp
 */

#include "../includes/Artillery.hpp"

Artillery::Artillery(Player *player)
    : Unit(player, 100, 2, 3, 2, 50, 30) {
}

Artillery::Artillery(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Artillery::~Artillery() {
    
}