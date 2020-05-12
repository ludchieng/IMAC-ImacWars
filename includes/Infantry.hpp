/*
 * Infantry.hpp
 */

#ifndef INFANTRY_HPP
#define INFANTRY_HPP

#include "../includes/Unit.hpp"

class Infantry : public Unit {

public:
    Infantry(int id, Player *player);
    Infantry(int id, Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def);
	~Infantry();

	bool canStandOn(Tile *t) const;
	bool canStandOn(LandType lt) const;

private:

};

#endif /* INFANTRY_HPP */
