/*
 * Texture.hpp
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../includes/Game.hpp"
#include "../includes/Model.hpp"
#include <vector>
using namespace std;

class TextureManager {

public:
    TextureManager();
    ~TextureManager();

    void fontColor3i(int r, int g, int b);
    void fontSize(float size) { m_fontSize = size; };
    void font(const char* file);

    void text(const char* text, double x, double y) const;

    int unit(Unit *u) const;

private:
    TTF_Font *m_font;
    const char *m_fontFile;
    float m_fontSize;
    SDL_Color m_fontColor;
    SDL_Color m_fontColorShadow;
    vector<int> m_duck;
    vector<int> m_bee;
    vector<int> m_hippo;
    int loadTex(const char *file);
    void drawText(SDL_Surface* surf, double x, double y) const;

};

#endif /* TEXTURE_HPP */
