/*
 * Artillery.cpp
 */

#include "../includes/Artillery.hpp"

Artillery::Artillery(int id, Player *player)
    : Unit(id, player, 100, 2, 3, 2, 50, 30) {
}

Artillery::Artillery(int id, Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(id, player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Artillery::~Artillery() {
    
}