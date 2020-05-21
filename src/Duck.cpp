/*
 * Duck.cpp
 */

#include "../includes/Duck.hpp"

Duck::Duck(Player *player)
    : Unit(player, 100, 4, 1, 2, 35, 45) {
}

Duck::Duck(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Duck::~Duck() {

}