/*
 * Infantry.cpp
 */

#include "../includes/Infantry.hpp"

Infantry::Infantry(int id, Player *player)
    : Unit(id, player, 100, 4, 1, 2, 35, 45) {
}

Infantry::Infantry(int id, Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
    : Unit(id, player, hpMax, mpMax, ratk, atkcost, atk, def) {
    
}

Infantry::~Infantry() {

}