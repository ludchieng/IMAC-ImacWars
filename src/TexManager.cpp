/**
 * TexManager.cpp
 */

#include "../includes/TexManager.hpp"

int TexManager::loadTex(const char *file) {
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

void TexManager::load(vector<int> *glTextures) {
	const char *files[] = {
		"assets/unit-blue-1-east.png",
		"assets/unit-red-1-west.png"
	};
	for (int i = 0; i < 2; i++) {
		glTextures->push_back(TexManager::loadTex(files[i]));
	}
}