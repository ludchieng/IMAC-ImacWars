/*
 * Game.cpp
 */

#include "../includes/Game.hpp"

const char Game::W_TITLE[] = "Imac Wars";
const float Game::GL_VIEW_SIZE = 200.;
SDL_Renderer *Game::renderer = NULL;

Game::Game(bool fullscreen) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		exit(600);

	int flags = SDL_WINDOW_OPENGL;
	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	renderer = SDL_CreateRenderer(m_window, -1, 0);
	
	m_window = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, flags);

	m_gl = SDL_GL_CreateContext(m_window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 20, 20, 0);

	c = new Controller();
	m_isRunning = true;
}

Game::~Game() {
	quit();
	delete c;
}

void Game::startLoop() {
	m_startTime = SDL_GetTicks();
}

void Game::handleEvents() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
			case SDL_QUIT:
				m_isRunning = false;
				break;
			case SDL_MOUSEBUTTONUP:
				printf("clic en (%d, %d)\n", e.button.x, e.button.y);
				break;
			case SDL_KEYDOWN:
				printf("touche pressee (code = %d)\n", e.key.keysym.sym);
				break;
			default:
				c->handle(&e);
				break;
		}
	}
}

void Game::update() {
	
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	c->v->render();
	SDL_GL_SwapWindow(m_window);
}

void Game::endLoop() {
	Uint32 elapsedTime = SDL_GetTicks() - m_startTime;
	if(elapsedTime < 1000 / FRAMERATE) 
		SDL_Delay(1000 / FRAMERATE - elapsedTime);
}

void Game::quit() {
	SDL_GL_DeleteContext(m_gl);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}