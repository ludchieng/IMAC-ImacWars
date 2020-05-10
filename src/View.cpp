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
    renderAstar();
}

void View::renderMap() {
    float thrs[] = {.35, .45, .65, .8};
    Map *map = m->getMap();
    for (int j = 0; j < map->getSizeY(); j++) {
        for (int i = 0; i < map->getSizeX(); i++) {
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
            glRecti(i, j, i+1, j+1);
        }
    }
}

//TODO remove
#include "../includes/Astar.hpp"

void View::renderAstar() {
    Map* map = m->getMap();
    Tile* start;
    Tile* target;
    do {
        start = map->getRandTile(true);
        target = map->getRandTile(true);
    } while(start == target);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    Player* p = new Player(1);
    Unit* u = new Unit(1, p, Unit::Type::Infantry);
    u->setTile(start);
    Astar::Node *path = Astar::exec(map, start, target, u);
    if (path != NULL) {
        Astar::Node *curr = path;
        do {
            glColor4ub(0, 200, 200, 150);
            glRecti((int) curr->pos->x, (int) curr->pos->y, (int) curr->pos->x+1, (int) curr->pos->y+1);
            curr = curr->next;
        } while(curr->next != NULL);
    }
    glColor4ub(255, 20, 255, 255);
    glRecti(start->getPosX(), start->getPosY(), start->getPosX()+1, start->getPosY()+1);
    glColor4ub(255, 255, 20, 255);
    glRecti(target->getPosX(), target->getPosY(), target->getPosX()+1, target->getPosY()+1);
}

void View::free() {

}
