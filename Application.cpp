#include "Controller.h"
#include <stdio.h>

int main (void) {
	Controller* c = new Controller();
    printf("End\n");
    delete c;
	return 0;
}
