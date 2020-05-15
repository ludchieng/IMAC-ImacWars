/*
 * Texture.hpp
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../includes/Game.hpp"
#include "../includes/Model.hpp"
#include <vector>
using namespace std;

class Texture {

public:
    Texture();
    ~Texture();
    int unit(Unit *u);

private:
    vector<int> m_infantry;
    vector<int> m_artillery;
    vector<int> m_tank;
    int loadTex(const char *file);

};

#endif /* TEXTURE_HPP */
