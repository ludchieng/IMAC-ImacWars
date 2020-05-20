#include "../includes/Game.hpp"

int main (void) {
	Game* g = new Game(true, false);
    while (g->isRunning()) {
        g->startLoop();
        g->render();
        g->handleEvents();
        g->update();
        g->endLoop();
    }
    g->quit();
    delete g;
	return 0;
}
