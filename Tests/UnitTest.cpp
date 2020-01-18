#include <iostream>
using namespace std;
#include "../Unit.h"
#include "../Tile.h"
#include "../Map.h"

int main(void) {
	Map* m = new Map(15, 6);
	cout << m->getTile(0,0)->toString();
	//cout << m->toString();
	Unit* u1 = new Unit(1, 0);
	Unit* u2 = new Unit(2, 1);
	u1->attack(u2);
	cout << u1->toString();
	cout << u2->toString();

	return 0;
}
