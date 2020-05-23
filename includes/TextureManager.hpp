/*
 * Texture.hpp
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../includes/Game.hpp"
#include "../includes/Model.hpp"
#include <string>
#include <vector>
using namespace std;

class TextureManager {

public:
    TextureManager();
    ~TextureManager();

    void setFrame(long int f) { m_frame = f; }

    void fontColor3i(int r, int g, int b);
    void fontOpacity(int o) { m_fontOpacity = o; }
    void fontSize(float size) { m_fontSize = size; };
    void font(const char* file);

    void text(const char* text, double x, double y) const;
    void text(string *text, double x, double y) const;
	void square(double x, double y);
	void square(double x, double y, int r, int g, int b);
	void square(double x, double y, int r, int g, int b, int a);
	void square(double x, double y, int idTex, float scale);

    int guiBg() const { return m_guiBg; }
    int guiBtnEndTurn(int state) const { return m_guiBtnEndTurn[state]; }
    int guiHead(int idPlayer) const { return m_guiHead[idPlayer]; }
    int unit(Unit *u) const;
    int tile(Tile *t) const;
    int cursorAttack() const { return m_cursorAttack[m_frame % m_cursorAttack.size()]; };
    int cursorMoves() const { return m_cursorMoves[m_frame % m_cursorMoves.size()]; };
    int cursorSelect() const { return m_cursorSelect[m_frame % m_cursorSelect.size()]; };
    Uint32 hash(Tile *t) const;

private:
    TTF_Font *m_font;
    const char *m_fontFile;
    float m_fontSize;
    SDL_Color m_fontColor;
    SDL_Color m_fontColorShadow;
    int m_fontOpacity;
    long int m_frame = 0;

    int m_guiBg;
    vector<int> m_guiBtnEndTurn;
    vector<int> m_guiHead;
    vector<int> m_duck[2];
    vector<int> m_bee[2];
    vector<int> m_rhino[2];
    vector<int> m_cursorAttack;
    vector<int> m_cursorMoves;
    vector<int> m_cursorSelect;
    vector<int> m_forest;
    vector<int> m_grass;
    vector<int> m_mountain;
    vector<int> m_sand;
    vector<int> m_sea;

    list<vector<int>*> m_textures;
    int loadTex(const char *file);
    void drawText(SDL_Surface* surf, double x, double y) const;

};

#endif /* TEXTURE_HPP */
