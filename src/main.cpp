#include <stdio.h>
#include "Controller.h"

int main (void) {
	Controller* c = new Controller();
    printf("\n\n");
    delete c;
	return 0;
}
