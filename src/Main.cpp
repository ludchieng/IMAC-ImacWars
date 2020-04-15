#include "Game.hpp"

int main (void) {
	Game* g = new Game();
    g->init();
    while (g->isRunning()) {
        g->handleEvents();
        g->update();
        g->render();
    }
    g->quit();
    delete g;
	return 0;
}
