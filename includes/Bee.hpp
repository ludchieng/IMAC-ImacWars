/*
 * Bee.hpp
 */

#ifndef BEE_HPP
#define BEE_HPP

#include "../includes/Unit.hpp"

class Bee : public Unit {

public:
    Bee(Player *player);
    Bee(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def);
	~Bee();
	
private:

};

#endif /* BEE_HPP */
