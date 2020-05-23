/*
 * Rhino.hpp
 */

#ifndef RHINO_HPP
#define RHINO_HPP

#include "../includes/Unit.hpp"

class Rhino : public Unit {

public:
    Rhino(Player *player);
    Rhino(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def);
	~Rhino();

private:

};

#endif /* RHINO_HPP */
