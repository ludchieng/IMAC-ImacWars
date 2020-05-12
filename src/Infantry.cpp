/*
 * Infantry.cpp
 */

#include "../includes/Infantry.hpp"

Infantry::Infantry(Player *player)
    : Unit(player, 100, 4, 1, 2, 35, 45) {
}

Infantry::Infantry(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Infantry::~Infantry() {

}