/*
 * Astar.cpp
 */

#include "../includes/Astar.hpp"

Astar::Node *Astar::exec(vector<vector<Node*>> &grid,  Node *nStart, Node *nTarget) {
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