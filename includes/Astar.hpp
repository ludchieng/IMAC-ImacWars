/*
 * Astar.hpp
 */

#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "../includes/Unit.hpp"
#include "../includes/Map.hpp"
#include "../includes/Tile.hpp"
#include "../includes/Vector2i.hpp"
#include <vector>
#include <list>
#include <algorithm>

class Map;

class Astar {
public:
    class Node;

    Astar();
    ~Astar();

    static Node *exec(Map *map,Tile *start, Tile *target, Unit *unit);
    static Node *exec(Map *map, Vector2i start, Vector2i target, Unit *unit);

private:

    static float computeHeuristics(Node *a, Node *b);
    static Node *reconstructPath(Node *target);

};


class Astar::Node {
public:
    Node(Vector2i *pos, bool isWall);
    Node(int x, int y, bool isWall);
    ~Node();

    void setNeighbours(vector<vector<Node*>>& grid);
    vector<Node*> getNeighbours() const;
    void copy(Node* n);

    Vector2i *pos;
    bool isWall;
    float f, g, h;
    Node *prev;
    Node *next;

    Node *top;
    Node *right;
    Node *bottom;
    Node *left;
};


#endif /* ASTAR_HPP */
