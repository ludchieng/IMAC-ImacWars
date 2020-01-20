/**
 * exceptions.cpp
 */

#include <exception>
using namespace std;


#ifndef NO_SUCH_UNIT
#define NO_SUCH_UNIT

class NoSuchUnit : public exception {
public:
	const char* what() {
		return "No such unit";
	}
};

#endif /* NO_SUCH_UNIT */


#ifndef NO_SUCH_TILE
#define NO_SUCH_TILE

class NoSuchTile : public exception {
public:
	const char* what() {
		return "No such tile";
	}
};

#endif /* NO_SUCH_TILE */


#ifndef OUT_OF_BOUND
#define OUT_OF_BOUND

class OutOfBound : public exception {
public:
	const char* what() {
		return "Out of bound";
	}
};

#endif /* OUT_OF_BOUND */


#ifndef ILLEGAL_STATE
#define ILLEGAL_STATE

class IllegalState : public exception {
public:
	const char* what() {
		return "Illegal state";
	}
};

#endif /* ILLEGAL_STATE */


#ifndef ILLEGAL_STATE_NOT_ENOUGH_MP
#define ILLEGAL_STATE_NOT_ENOUGH_MP

class IllegalStateNotEnoughMP : public IllegalState {
public:
	const char* what() {
		return "Illegal state not enough MP";
	}
};

#endif /* ILLEGAL_STATE_NOT_ENOUGH_MP */


#ifndef ILLEGAL_ARGUMENT
#define ILLEGAL_ARGUMENT

class IllegalArgument : public exception {
public:
	const char* what() {
		return "Illegal argument";
	}
};

#endif /* ILLEGAL_ARGUMENT */


#ifndef ILLEGAL_UNIT_SELECTION
#define ILLEGAL_UNIT_SELECTION

class IllegalUnitSelection : public exception {
public:
	const char* what() {
		return "Illegal unit selection";
	}
};

#endif /* ILLEGAL_UNIT_SELECTION */


#ifndef ILLEGAL_MOVE_OUT_OF_RANGE
#define ILLEGAL_MOVE_OUT_OF_RANGE

class IllegalMoveOutOfRange : public exception {
public:
	const char* what() {
		return "Illegal move out of range";
	}
};

#endif /* ILLEGAL_MOVE_OUT_OF_RANGE */


#ifndef ILLEGAL_MOVE_OCCUPIED_TILE
#define ILLEGAL_MOVE_OCCUPIED_TILE

class IllegalMoveOccupiedTile : public exception {
public:
	const char* what() {
		return "Illegal move occupied tile";
	}
};

#endif /* ILLEGAL_MOVE_OCCUPIED_TILE */


#ifndef ILLEGAL_ATTACK_OUT_OF_RANGE
#define ILLEGAL_ATTACK_OUT_OF_RANGE

class IllegalAttackOutOfRange : public exception {
public:
	const char* what() {
		return "Illegal attack out of range";
	}
};

#endif /* ILLEGAL_ATTACK_OUT_OF_RANGE */


#ifndef ILLEGAL_ATTACK_FRIENDLY_FIRE
#define ILLEGAL_ATTACK_FRIENDLY_FIRE

class IllegalAttackFriendlyFire : public exception {
public:
	const char* what() {
		return "Illegal attack friendly fire";
	}
};

#endif /* ILLEGAL_ATTACK_FRIENDLY_FIRE */
