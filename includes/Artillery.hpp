/*
 * Artillery.hpp
 */

#ifndef ARTILLERY_HPP
#define ARTILLERY_HPP

#include "../includes/Unit.hpp"

class Artillery : public Unit {

public:
    Artillery(int id, Player *player);
    Artillery(int id, Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def);
	~Artillery();
	
private:

};

#endif /* ARTILLERY_HPP */
