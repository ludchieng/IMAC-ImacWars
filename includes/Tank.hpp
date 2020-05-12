/*
 * Tank.hpp
 */

#ifndef TANK_HPP
#define TANK_HPP

#include "../includes/Unit.hpp"

class Tank : public Unit {

public:
    Tank(int id, Player *player);
    Tank(int id, Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def);
	~Tank();

private:

};

#endif /* TANK_HPP */
