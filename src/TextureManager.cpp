/**
 * Texture.cpp
 */

#include "../includes/TextureManager.hpp"

TextureManager::TextureManager() {
	m_font = NULL;
	m_fontFile = "assets/fonts/BalsamiqSans-Bold.ttf";
	m_fontSize = .5;
	font(m_fontFile);
	fontColor3i(255, 255, 255);
	m_duck.push_back(TextureManager::loadTex("assets/unit-blue-1-east.png"));
	m_duck.push_back(TextureManager::loadTex("assets/unit-blue-1-west.png"));
	m_duck.push_back(TextureManager::loadTex("assets/unit-red-1-east.png"));
	m_duck.push_back(TextureManager::loadTex("assets/unit-red-1-west.png"));
}

TextureManager::~TextureManager() {
	// Delete all textures
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
        fprintf(stderr, "Failed to load font at %s", file);
        exit(EXIT_FAILURE);
    }
	m_font = tmp;
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
	glDeleteTextures(1, &idTex);
	SDL_FreeSurface(surf);
}

int TextureManager::unit(Unit *u) const {
	int idPlayer = u->getPlayer()->getId();
	return m_duck[idPlayer*2];
}