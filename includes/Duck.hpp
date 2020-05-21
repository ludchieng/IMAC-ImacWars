/*
 * Duck.hpp
 */

#ifndef DUCK_HPP
#define DUCK_HPP

#include "../includes/Unit.hpp"

class Duck : public Unit {

public:
    Duck(Player *player);
    Duck(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def);
	~Duck();

	bool canStandOn(Tile *t) const;
	bool canStandOn(Land::Type lt) const;

private:

};

#endif /* DUCK_HPP */
