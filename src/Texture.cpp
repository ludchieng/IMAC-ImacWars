/**
 * Texture.cpp
 */

#include "../includes/Texture.hpp"

Texture::Texture() {
	m_infantry.push_back(Texture::loadTex("assets/unit-blue-1-east.png"));
	m_infantry.push_back(Texture::loadTex("assets/unit-blue-1-west.png"));
	m_infantry.push_back(Texture::loadTex("assets/unit-red-1-east.png"));
	m_infantry.push_back(Texture::loadTex("assets/unit-red-1-west.png"));
}

int Texture::loadTex(const char *file) {
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
	return idTex;
}

int Texture::unit(Unit *u) {
	int idPlayer = u->getPlayer()->getId();
	return m_infantry[idPlayer*2];
}