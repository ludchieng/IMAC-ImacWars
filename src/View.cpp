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

void View::update() {
	list<Entity*> toDelete;
    for (Entity *e : *getEntities())
		if (!e->update())
			toDelete.push_back(e);
    for (Entity *e : toDelete)
		delEntity(e);
}

void View::render(long int counter, Vector2d cursorPos) {
	int xi = (int) (cursorPos.x >= 0.) ? cursorPos.x : cursorPos.x-1;
	int yi = (int) (cursorPos.y >= 0.) ? cursorPos.y : cursorPos.y-1;
    Tile *t = NULL;
	if (xi >= 0 && xi < m->getMap()->getSizeX()
	 && yi >= 0 && yi < m->getMap()->getSizeY()) {
		// Cursor is on map
		t = m->getMap()->getTile(xi, yi);
	}
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    renderMap();
    renderMapUI();
    renderUnits();
    renderEntities();
    renderGUI(cursorPos);
    if (t != NULL) {
		renderTileCursor(t);
    }
    if (m->hasWinner())
        renderVictory();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    if (counter % FRAME_LENGTH == 0)
        tex->setFrame(m_frame++);
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
                    new Color(255, 230, 150), new Color(230, 220, 120),
                    Map::LIMIT_COAST, Map::LIMIT_SHORE, alt);
                break;
            case Land::Type::PLAIN:
                c = Color::lerp(
                    new Color(150, 120, 82), new Color(75, 130, 62),
                    Map::LIMIT_SHORE, Map::LIMIT_PLAIN, alt);
                break;
            case Land::Type::FOREST:
                c = Color::lerp(
                    new Color(75, 130, 62), new Color(70, 125, 60),
                    Map::LIMIT_PLAIN, Map::LIMIT_FOREST, alt);
                break;
            case Land::Type::MOUNTAIN:
                c = Color::lerp(
                    new Color(110, 140, 90), new Color(110, 140, 90),
                    Map::LIMIT_FOREST, Map::LIMIT_MOUNTAIN, alt);
                break;
            case Land::Type::PEAK:
                c = Color::lerp(
                    new Color(110, 140, 90), new Color(130, 150, 100),
                    Map::LIMIT_MOUNTAIN, Map::LIMIT_PEAK, alt);
                break;
            }
            tex->square(i, j, c.r, c.g, c.b);
        }
    }
    for (int j = 0; j < map->getSizeY(); j++) {
        for (int i = 0; i < map->getSizeX(); i++) {
            Tile *t = map->getTile(i, j);
            tex->square(i, j, tex->tile(t), 2.);
        }
    }
}

void View::renderMapUI() {
    if (m->hasSelectedUnit()) {
        Unit *u = m->getSelectedUnit();
        list<Tile*> *pMoves = m->getSelectedUnitPossibleMoves();
        for (Tile *t : *pMoves) {
            tex->square(t->getPosX(), t->getPosY(), tex->cursorMoves(), 2.);
        }
        list<Tile*> *pAttacks = m->getSelectedUnitPossibleAttacks();
        for (Tile *t : *pAttacks) {
            tex->square(t->getPosX(), t->getPosY(), tex->cursorAttack(), 2.);
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
    tex->fontColor3i(255, 255, 255);
    tex->fontSize(0.47);
    tex->fontOpacity(255);
    for (Player *p : m->getPlayers()) {
        for (Unit *u : *(p->getUnits())) {
            Vector2i pos = u->getTile()->getPos();
            tex->square(pos.x, pos.y, tex->unit(u), 1.6);
            tex->text(to_string(u->getHp()).c_str(), pos.x, pos.y);
        }
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void View::renderTileCursor(Tile *t) {
    int x = t->getPosX();
    int y = t->getPosY();
    Unit *tu = t->getUnit();
    Unit *su = m->getSelectedUnit();
    Player *pt = m->getPlayerTurn();
    if (tu != NULL) {
        if (tu->getPlayer() == pt && !m->isAI(pt))
            tex->square(x, y, tex->cursorSelect(), 2.);
        else if (su != NULL && su->canAttack(tu))
            tex->square(x, y, tex->cursorAttack(), 2.);
    } else {
        if (su != NULL && m->unitCanMoveOn(su, t))
                tex->square(x, y, tex->cursorSelect(), 2.);
    }
}

void View::renderEntities() {
    for (Entity *e : m_entities)
        e->render(tex);
}

void View::renderGUI(Vector2d cursorPos) {
    float mapW = m->getMap()->getSizeX();
    float mapH = m->getMap()->getSizeY();
    float header_h_gl = 1.5;
    float footer_h_gl = .35;
    float top = -header_h_gl;
    float right = mapW + 4.55;
    float bottom = mapH + footer_h_gl;
    float left = -4.55;
    glBindTexture(GL_TEXTURE_2D, tex->guiBg());
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0);
        glVertex2f(left, top);
        glTexCoord2i(0, 1);
        glVertex2f(left, bottom);
        glTexCoord2i(1, 1);
        glVertex2f(right, bottom);
        glTexCoord2i(1, 0);
        glVertex2f(right, top);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, tex->guiHead(m->getPlayerTurn()->getId()));
    glBegin(GL_QUADS);
        glTexCoord2f(0., 0.);
        glVertex2f(left, top);
        glTexCoord2f(0., .99);
        glVertex2f(left, top + header_h_gl);
        glTexCoord2f(1., .99);
        glVertex2f(right, top + header_h_gl);
        glTexCoord2f(1., 0.);
        glVertex2f(right, top);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    tex->fontColor3i(255, 255, 255);
    tex->fontSize(1.);
    tex->fontOpacity(255);
    tex->text(m->getPlayerTurn()->getName(), 0., top + .2);

    int btnState = (isHoverBtnNextTurn(cursorPos)) ? 1 : 0;
    glBindTexture(GL_TEXTURE_2D, tex->guiBtnEndTurn(btnState));
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0);
        glVertex2f(mapW - 2.5, top + .2);
        glTexCoord2i(0, 1);
        glVertex2f(mapW - 2.5, top + 1.);
        glTexCoord2i(1, 1);
        glVertex2f(mapW, top + 1.);
        glTexCoord2i(1, 0);
        glVertex2f(mapW, top + .2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void View::renderVictory() {
    double x = m->getMap()->getSizeX() / 2 - 1.5;
    double y = m->getMap()->getSizeY() / 2 - .5;
    tex->fontColor3i(255, 255, 255);
    tex->fontOpacity(255);
    tex->fontSize(.9);
    tex->text("Victoire !", x, y);
}

bool View::isHoverBtnNextTurn(Vector2d pos) const {
    float mapW = m->getMap()->getSizeX();
    float mapH = m->getMap()->getSizeY();
    float header_h_gl = 1.5;
    float footer_h_gl = .35;
    float top = -header_h_gl;
    float right = mapW + 4.55;
    float bottom = mapH + footer_h_gl;
    float left = -4.55;
    return pos.x > mapW - 2.5 && pos.x < mapW
        && pos.y > top + .2 && pos.y < top + 1.;
}
