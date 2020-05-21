/*
 * View.cpp
 */

#include "../includes/View.hpp"

View::View(Model *m) {
    this->m = m;
    this->tex = new TextureManager();
}

View::~View() {

}

void View::render() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    renderMap();
    renderMapUI();
    renderUnits();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
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

void View::renderMapUI() {
    if (m->hasSelectedUnit()) {
        Unit *u = m->getSelectedUnit();
        list<Tile*> *pMoves = m->getSelectedUnitPossibleMoves();
        for (Tile *t : *pMoves) {
            glPushMatrix();
            glColor4ub(100, 205, 255, 100);
            glTranslatef(t->getPosX(), t->getPosY(), 0.);
            glRecti(0, 0, 1, 1);
            glPopMatrix();
        }
    }
}

//TODO remove
/*#include "../includes/Astar.hpp"

void View::renderAstar() {
    Map *map = m->getMap();
    Tile *start = map->getSpawn(0);
    Tile *target = map->getSpawn(1);
    Player *p = new Player(1);
    Unit *u = new Duck(p);
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
    glColor4ub(255, 255, 20, 255);
    glRecti(target->getPosX(), target->getPosY(), target->getPosX()+1, target->getPosY()+1);
}*/

void View::renderUnits() {
    for (Player *p : m->getPlayers()) {
        for (Unit *u : *(p->getUnits())) {
            glBindTexture(GL_TEXTURE_2D, tex->unit(u));
            glPushMatrix();
                glTranslatef(u->pos.x, u->pos.y, 0.);
                glPushMatrix();
                    glTranslatef(.5, .5, 0.);
                    glScalef(1.1, 1.1, 1.);
                    glBegin(GL_QUADS);
                        glTexCoord2i(0, 0);
                        glVertex2f(-.5, -.5);
                        glTexCoord2i(0, 1);
                        glVertex2f(-.5, 0.5);
                        glTexCoord2i(1, 1);
                        glVertex2f(0.5, 0.5);
                        glTexCoord2i(1, 0);
                        glVertex2f(0.5, -.5);
                    glEnd();
                glPopMatrix();
                tex->text(to_string(u->getHp()).c_str(), 0, 0);
            glPopMatrix();
        }
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}
