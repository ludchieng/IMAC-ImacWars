/*
 * TexManager.hpp
 */

#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "../includes/Game.hpp"
#include <vector>

using namespace std;

class TexManager {

public:
    static int loadTex(const char *file);
    static void load(vector<int> *glTextures);

private:

};

#endif /* TEXTURE_MANAGER_HPP */
