/*
 * Hippo.hpp
 */

#ifndef HIPPO_HPP
#define HIPPO_HPP

#include "../includes/Unit.hpp"

class Hippo : public Unit {

public:
    Hippo(Player *player);
    Hippo(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def);
	~Hippo();

private:

};

#endif /* HIPPO_HPP */
