/*
 * Astar.cpp
 */

#include "../includes/Astar.hpp"

Astar::Node *Astar::exec(Map *map, Vector2i tStart, Vector2i tTarget, Unit *unit) {
    return exec(map, map->getTile(tStart), map->getTile(tTarget), unit);
}

Astar::Node *Astar::exec(Map *map, Tile *tStart, Tile *tTarget, Unit *unit) {
    if (tStart == tTarget)
        return NULL;

    vector<vector<Node*>> grid(map->getSizeX());
    
    for (int j = 0; j < map->getSizeY(); j++) {
        vector<Node*> v(map->getSizeX());
        grid[j] = v;
        for (int i = 0; i < map->getSizeX(); i++) {
            LandType lt = map->getTile(i, j)->getLandType();
            bool isWall = !unit->canStandOn(map->getTile(i, j));
            grid[j][i] = new Node(i, j, isWall);
        }
    }
    for (vector<Node*> v : grid)
        for (Node* n : v)
            n->setNeighbours(grid);

    Node *nStart = grid[tStart->getPosY()][tStart->getPosX()];
    Node *nTarget = grid[tTarget->getPosY()][tTarget->getPosX()];

    list<Node*> active;
    list<Node*> visited;
    active.push_back(nStart);
    Node *curr;
    while (active.size() > 0) {
        curr = active.front();
        for (Node* n : active)
            if (n->f < curr->f)
                curr = n;
        
        if (curr == nTarget)
            return reconstructPath(nTarget);
        
        active.remove(curr);
        visited.push_back(curr);

        for (Node* n : curr->getNeighbours()) {
            float g;
            if (find(visited.begin(), visited.end(), n) == visited.end()
                    && !n->isWall) {
                g = curr->g + computeHeuristics(curr, n);
                
                bool isBetterPath = false;
                if (find(active.begin(), active.end(), n) != active.end()) {
                    if (g < n->g) {
                        n->g = g;
                        isBetterPath = true;
                    }
                } else {
                    n->g = g;
                    isBetterPath = true;
                    active.push_back(n);
                }
                if (isBetterPath) {
                    n->h = computeHeuristics(n, nTarget);
                    n->f = n->g + n->h;
                    n->prev = curr;
                }
            }
        }
    }
    return NULL;
}

float Astar::computeHeuristics(Node *a, Node *b) {
    return (float) Vector2i::sub(a->pos, b->pos).mag();
}

Astar::Node *Astar::reconstructPath(Node *target) {
    Node *cursor = target;
    Node *next = NULL;
    do {
        cursor->next = next;
        Node* n = (Node*) malloc(sizeof(Node));
        n->copy(cursor);
        next = cursor;
        cursor = cursor->prev;
    } while (cursor->prev != NULL);
    cursor->next = next;
    Node *curr = cursor;
    return cursor;
}


Astar::Node::Node(Vector2i *pos, bool isWall) {
    Node(pos->x, pos->y, isWall);
}

Astar::Node::Node(int x, int y, bool isWall) {
    this->pos = new Vector2i(x, y);
    this->isWall = isWall;
    this->f = 0.;
    this->g = 0.;
    this->h = 0.;
    this->prev = NULL;
    this->next = NULL;
    this->top = NULL;
    this->right = NULL;
    this->bottom = NULL;
    this->left = NULL;
}

Astar::Node::~Node() {

}

void Astar::Node::setNeighbours(vector<vector<Node*>>& grid) {
    if (pos->x > 0)
        this->left = grid[pos->y][pos->x-1];
    if (pos->y > 0)
        this->top = grid[pos->y-1][pos->x];
    if (pos->x < grid[0].size()-1)
        this->right = grid[pos->y][pos->x+1];
    if (pos->y < grid.size()-1)
        this->bottom = grid[pos->y+1][pos->x];
}

vector<Astar::Node*> Astar::Node::getNeighbours() const {
    vector<Node*> res;
    if (top != NULL)
        res.push_back(top);
    if (left != NULL)
        res.push_back(left);
    if (bottom != NULL)
        res.push_back(bottom);
    if (right != NULL)
        res.push_back(right);
    return res;
}

void Astar::Node::copy(Node *n) {
    pos = n->pos;
    isWall = n->isWall;
    f = n->f;
    g = n->g;
    h = n->h;
    prev = n->prev;
    next = n->next;
    top = n->top;
    right = n->right;
    bottom = n->bottom;
    left = n->left;
}