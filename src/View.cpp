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
    renderUnits();
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
            case Land::Type::OCEAN:
                c = Color::lerp(
                    new Color(20, 60, 160), new Color(20, 90, 190),
                    0.0, Map::LIMIT_OCEAN, alt);
                break;
            case Land::Type::COAST:
                c = Color::lerp(
                    new Color(20, 90, 190), new Color(20, 140, 220),
                    Map::LIMIT_OCEAN, Map::LIMIT_COAST, alt);
                break;
            case Land::Type::SHORE:
                c = Color::lerp(
                    new Color(255, 230, 150), new Color(100, 140, 80),
                    Map::LIMIT_COAST, Map::LIMIT_PLAIN, alt);
                break;
            case Land::Type::PLAIN:
                c = Color::lerp(
                    new Color(90, 140, 75), new Color(85, 135, 72),
                    Map::LIMIT_PLAIN, Map::LIMIT_FOREST, alt);
                break;
            case Land::Type::FOREST:
                c = Color::lerp(
                    new Color(65, 95, 85), new Color(70, 100, 90),
                    Map::LIMIT_FOREST, Map::LIMIT_MOUNTAIN, alt);
                break;
            case Land::Type::MOUNTAIN:
                c = Color::lerp(
                    new Color(180, 175, 177), new Color(215, 210, 210),
                    Map::LIMIT_MOUNTAIN, Map::LIMIT_PEAK, alt);
                break;
            case Land::Type::PEAK:
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
    Map *map = m->getMap();
    Tile *start = map->getSpawn(0);
    Tile *target = map->getSpawn(1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    Player *p = new Player(1);
    Unit *u = new Infantry(p);
    u->setTile(start);
    Tile::Path path = map->findPath(start, target, Land::TYPE_FIELD);
    for (int i = 0; i < path.size; i++) {
        int x = path.tiles[i]->getPosX();
        int y = path.tiles[i]->getPosY();
        glColor4ub(0, 200, 200, 150);
        glRecti(x, y, x+1, y+1);
    }
    glColor4ub(255, 20, 255, 255);
    glRecti(start->getPosX(), start->getPosY(), start->getPosX()+1, start->getPosY()+1);
    /*for (int i = 0; i < 3; i++) {
        Tile *t = map->getRandTileNear(start, 2, Land::TYPE_FIELD);
        glColor4ub(255, 20, 255, 150);
        glRecti(t->getPosX(), t->getPosY(), t->getPosX()+1, t->getPosY()+1);
    }*/
    
    glColor4ub(255, 255, 20, 255);
    glRecti(target->getPosX(), target->getPosY(), target->getPosX()+1, target->getPosY()+1);
    /*for (int i = 0; i < 3; i++) {
        Tile *t = map->getRandTileNear(target, 2, Land::TYPE_FIELD);
        glColor4ub(255, 255, 20, 150);
        glRecti(t->getPosX(), t->getPosY(), t->getPosX()+1, t->getPosY()+1);
    }*/
}

void View::renderUnits() {
    glColor4ub(255, 0, 100, 150);
    for (Player *p : m->getPlayers()) {
        for (Unit *u : p->getUnits()) {
            Vector2i pos = u->getTile()->getPos();
            glRecti(pos.x, pos.y, pos.x+1, pos.y+1);
        }
    }
}

void View::free() {

}
