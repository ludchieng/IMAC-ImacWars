/**
 * Texture.cpp
 */

#include "../includes/TextureManager.hpp"

TextureManager::TextureManager() {
	m_font = NULL;
	m_fontFile = "assets/fonts/BalsamiqSans-Bold.ttf";
	m_fontSize = .5;
	m_fontOpacity = 255;
	font(m_fontFile);
	fontColor3i(255, 255, 255);

	m_guiBg = TextureManager::loadTex("assets/gui-bg.png");
	m_guiBtnEndTurn.push_back(TextureManager::loadTex("assets/gui-btn-end-turn.png"));
	m_guiBtnEndTurn.push_back(TextureManager::loadTex("assets/gui-btn-end-turn-hover.png"));
	m_guiBtnEndTurn.push_back(TextureManager::loadTex("assets/gui-btn-end-turn-active.png"));
	m_textures.push_back(&m_guiBtnEndTurn);

	m_guiHead.push_back(TextureManager::loadTex("assets/gui-head-blue.png"));
	m_guiHead.push_back(TextureManager::loadTex("assets/gui-head-red.png"));
	m_textures.push_back(&m_guiHead);

	m_duck[0].push_back(TextureManager::loadTex("assets/duck-blue-1.png"));
	m_textures.push_back(&m_duck[0]);
	m_duck[1].push_back(TextureManager::loadTex("assets/duck-red-1.png"));
	m_textures.push_back(&m_duck[1]);
	m_bee[0].push_back(TextureManager::loadTex("assets/bee-blue-1.png"));
	m_textures.push_back(&m_bee[0]);
	m_bee[1].push_back(TextureManager::loadTex("assets/bee-red-1.png"));
	m_textures.push_back(&m_bee[1]);
	m_rhino[0].push_back(TextureManager::loadTex("assets/rhino-blue-1.png"));
	m_textures.push_back(&m_rhino[0]);
	m_rhino[1].push_back(TextureManager::loadTex("assets/rhino-red-1.png"));
	m_textures.push_back(&m_rhino[1]);

	m_cursorAttack.push_back(TextureManager::loadTex("assets/cursor-attack-1.png"));
	m_cursorAttack.push_back(TextureManager::loadTex("assets/cursor-attack-2.png"));
	m_textures.push_back(&m_cursorAttack);
	m_cursorMoves.push_back(TextureManager::loadTex("assets/cursor-moves-1.png"));
	m_cursorMoves.push_back(TextureManager::loadTex("assets/cursor-moves-2.png"));
	m_textures.push_back(&m_cursorMoves);
	m_cursorSelect.push_back(TextureManager::loadTex("assets/cursor-select-1.png"));
	m_cursorSelect.push_back(TextureManager::loadTex("assets/cursor-select-2.png"));
	m_textures.push_back(&m_cursorSelect);

	m_forest.push_back(TextureManager::loadTex("assets/forest-1.png"));
	m_forest.push_back(TextureManager::loadTex("assets/forest-2.png"));
	m_forest.push_back(TextureManager::loadTex("assets/forest-3.png"));
	m_forest.push_back(TextureManager::loadTex("assets/forest-4.png"));
	m_forest.push_back(TextureManager::loadTex("assets/forest-5.png"));
	m_textures.push_back(&m_forest);
	m_grass.push_back(TextureManager::loadTex("assets/grass-1.png"));
	m_grass.push_back(TextureManager::loadTex("assets/grass-2.png"));
	m_grass.push_back(TextureManager::loadTex("assets/grass-3.png"));
	m_textures.push_back(&m_grass);
	m_mountain.push_back(TextureManager::loadTex("assets/mountain-1.png"));
	m_mountain.push_back(TextureManager::loadTex("assets/mountain-2.png"));
	m_mountain.push_back(TextureManager::loadTex("assets/mountain-3.png"));
	m_mountain.push_back(TextureManager::loadTex("assets/mountain-4.png"));
	m_mountain.push_back(TextureManager::loadTex("assets/mountain-5.png"));
	m_textures.push_back(&m_mountain);
	m_sand.push_back(TextureManager::loadTex("assets/sand-1.png"));
	m_sand.push_back(TextureManager::loadTex("assets/sand-2.png"));
	m_sand.push_back(TextureManager::loadTex("assets/sand-3.png"));
	m_textures.push_back(&m_sand);
	m_sea.push_back(TextureManager::loadTex("assets/sea-1.png"));
	m_sea.push_back(TextureManager::loadTex("assets/sea-2.png"));
	m_textures.push_back(&m_sea);
}

TextureManager::~TextureManager() {
	for (vector<int> *v : m_textures) {
		for (GLuint idTex : *v) {
			glDeleteTextures(1, &idTex);
		}
	}
}

int TextureManager::loadTex(const char *file) {
	SDL_Surface *surf = IMG_Load(file);
	if (surf == NULL) {
		fprintf(stderr, "Failed to load texture at %s\n", file);
		exit(EXIT_FAILURE);
	}
	GLenum format;
	switch (surf->format->BytesPerPixel) {
	case 1:
		format = GL_RED;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		fprintf(stderr, "Unknown image format\n");
		exit(EXIT_FAILURE);
	}
	GLuint idTex;
	glGenTextures(1, &idTex);
	glBindTexture(GL_TEXTURE_2D, idTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w,surf->h,
		0, format, GL_UNSIGNED_BYTE, surf->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(surf);
	return idTex;
}

void TextureManager::fontColor3i(int r, int g, int b) {
	SDL_Color face = { (Uint8) r, (Uint8) g, (Uint8) b};
	SDL_Color shadow = { (Uint8) (r/5), (Uint8) (g/5), (Uint8) (b/5) };
	m_fontColor = face;
	m_fontColorShadow = shadow;
}

void TextureManager::font(const char* file) {
	if (m_font != NULL)
		TTF_CloseFont(m_font);
    TTF_Font *tmp = TTF_OpenFont(file, 48);
    if (tmp == NULL) {
        fprintf(stderr, "Failed to load font at %s\n", file);
        exit(EXIT_FAILURE);
    }
	m_font = tmp;
}

void TextureManager::text(string *text, double x, double y) const {
	this->text(text->c_str(), x, y);
}

void TextureManager::text(const char* text, double x, double y) const {
    SDL_Surface *face = TTF_RenderText_Blended(m_font, text, m_fontColor);
    SDL_Surface *shdw = TTF_RenderText_Blended(m_font, text, m_fontColorShadow);
	float shdwDist = m_fontSize/20;
	drawText(shdw, x + shdwDist, y + shdwDist);
	drawText(face, x, y);
}

void TextureManager::drawText(SDL_Surface* surf, double x, double y) const {
	float ratio = surf->w / (float) surf ->h;
	GLuint idTex;
	glGenTextures(1, &idTex);
	glBindTexture(GL_TEXTURE_2D, idTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glColor4ub(255, 255, 255, m_fontOpacity);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w,surf->h,
		0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
    glPushMatrix();
		glTranslatef(x, y, 0.);
        glBegin(GL_QUADS);
            glTexCoord2i(0,0);
            glVertex2f(0,0);
            glTexCoord2i(0,1);
            glVertex2f(0,m_fontSize);
            glTexCoord2i(1,1);
            glVertex2f(m_fontSize*ratio,m_fontSize);
            glTexCoord2i(1,0);
            glVertex2f(m_fontSize*ratio,0);
        glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDeleteTextures(1, &idTex);
	SDL_FreeSurface(surf);
}

void TextureManager::square(double x, double y) {
    glPushMatrix();
    glTranslatef(x, y, 0.);
    glRecti(0, 0, 1, 1);
    glPopMatrix();
}

void TextureManager::square(double x, double y, int r, int g, int b) {
    square(x, y, r, g, b, 255);
}

void TextureManager::square(double x, double y, int r, int g, int b, int a) {
    glPushMatrix();
    glColor4ub(r, g, b, a);
    glTranslatef(x, y, 0.);
    glRecti(0, 0, 1, 1);
    glPopMatrix();
}


void TextureManager::square(double x, double y, int idTex, float scale) {
    if (idTex == 0)
        return;
    glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, idTex);
        glTranslated(x, y, 0);
		glTranslatef(.5, .5, 0.);
		glScalef(scale, scale, 1.);
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
		glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

int TextureManager::unit(Unit *u) const {
	int res;
	int idPlayer = u->getPlayer()->getId();
	if (NULL != dynamic_cast<Duck*>(u))
		res = m_duck[idPlayer][m_frame % m_duck[idPlayer].size()];
	else if (NULL != dynamic_cast<Bee*>(u))
		res = m_bee[idPlayer][m_frame % m_bee[idPlayer].size()];
	else if (NULL != dynamic_cast<Rhino*>(u))
		res = m_rhino[idPlayer][m_frame % m_rhino[idPlayer].size()];
	else
		fprintf(stderr, "Failed to load unit texture: unknown unit type\n");
	
	return res;
}

int TextureManager::tile(Tile *t) const {
	unsigned int h = t->getHash();
	Land::Type lt = t->getLandType();
	switch (lt) {
	case Land::Type::OCEAN:
	case Land::Type::COAST:
		return m_sea[h % m_sea.size()];
	case Land::Type::SHORE:
		return m_sand[h % m_sand.size()];
	case Land::Type::PLAIN:
		return m_grass[h % m_grass.size()];
	case Land::Type::FOREST:
		return m_forest[h % m_forest.size()];
	case Land::Type::MOUNTAIN:
	case Land::Type::PEAK:
		return m_mountain[h % m_mountain.size()];
	}
}