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
            Tile *t = map->getTile(i, j);
            float alt = t->getAltitude();
            Color c;
            switch (t->getLandType()) {
            case Tile::LandType::OCEAN:
                c = Color::lerp(
                    new Color(20, 60, 160), new Color(20, 90, 190),
                    0.0, Map::LIMIT_OCEAN, alt);
                break;
            case Tile::LandType::COAST:
                c = Color::lerp(
                    new Color(20, 90, 190), new Color(20, 140, 220),
                    Map::LIMIT_OCEAN, Map::LIMIT_COAST, alt);
                break;
            case Tile::LandType::SHORE:
                c = Color::lerp(
                    new Color(255, 230, 150), new Color(100, 140, 80),
                    Map::LIMIT_COAST, Map::LIMIT_PLAIN, alt);
                break;
            case Tile::LandType::PLAIN:
                c = Color::lerp(
                    new Color(90, 140, 75), new Color(85, 135, 72),
                    Map::LIMIT_PLAIN, Map::LIMIT_FOREST, alt);
                break;
            case Tile::LandType::FOREST:
                c = Color::lerp(
                    new Color(65, 95, 85), new Color(70, 100, 90),
                    Map::LIMIT_FOREST, Map::LIMIT_MOUNTAIN, alt);
                break;
            case Tile::LandType::MOUNTAIN:
                c = Color::lerp(
                    new Color(180, 175, 177), new Color(215, 210, 210),
                    Map::LIMIT_MOUNTAIN, Map::LIMIT_PEAK, alt);
                break;
            case Tile::LandType::PEAK:
                c = Color::lerp(
                    new Color(220, 220, 225), new Color(255, 255, 255),
                    Map::LIMIT_PEAK, 1.0, alt);
                break;
            }
            glColor3ub(c.r, c.g, c.b);
            glRecti(j, i, j+1, i+1);
        }
    }
}

void View::free() {

}
