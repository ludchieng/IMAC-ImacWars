/*
 * View.cpp
 */

#include "../includes/View.hpp"

View::View(Model *m) {
    this->m = m;
}

View::~View() {

}

void View::render() {
    renderMap();
}

void View::renderMap() {
    float thrs[] = {.35, .45, .65, .8};
    Map *map = m->getMap();
    for (int i = 0; i < map->getSizeY(); i++) {
        for (int j = 0; j < map->getSizeX(); j++) {
            float alt = map->getTile(i, j)->getAltitude();
            glColor3ub(255, 255, 255);
            if (alt < thrs[0]) {
                glColor3ub(20, 100, 150);
            } else if (alt < thrs[1]) {
                glColor3ub(220, 200, 150);
            } else if (alt < thrs[2]) {
                glColor3ub(80, 140, 60);
            } else if (alt < thrs[3]) {
                glColor3ub(80, 125, 70);
            } else {
                glColor3ub(120, 130, 110);
            }
            glRecti(j, i, j+1, i+1);
        }
    }
}

void View::free() {

}
