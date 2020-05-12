/*
 * Artillery.hpp
 */

#ifndef ARTILLERY_HPP
#define ARTILLERY_HPP

#include "../includes/Unit.hpp"

class Artillery : public Unit {

public:
    Artillery(Player *player);
    Artillery(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def);
	~Artillery();
	
private:

};

#endif /* ARTILLERY_HPP */
