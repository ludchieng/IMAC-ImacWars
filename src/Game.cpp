/*
 * Game.cpp
 */

#include "../includes/Game.hpp"

const char Game::W_TITLE[] = "Imac Wars";
//const float Game::GL_VIEW_SIZE = 200.;
SDL_Renderer *Game::renderer = NULL;

Game::Game(bool againstComputer, bool fullscreen) {
	SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
	renderer = SDL_CreateRenderer(m_window, -1, 0);

	int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	if (fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;
	
	m_window = SDL_CreateWindow(W_TITLE, 1000, //TODO replace SDL_WINDOWPOS_CENTERED
		SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, flags);

	m_gl = SDL_GL_CreateContext(m_window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	reshape();

	c = new Controller(againstComputer, MAP_SIZE);
	m_isRunning = true;
}

Game::~Game() {
	quit();
	delete c;
}

void Game::reshape() {
	int w = getWindowWidth();
	int h = getWindowHeight();
	glViewport(0., 0., w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Vector2i sdlSize(w,h);
	Vector2d topLeft = coordsSDLtoGL(0, 0);
	Vector2d bottomRight = coordsSDLtoGL(sdlSize.x, sdlSize.y);
	gluOrtho2D(topLeft.x, bottomRight.x, bottomRight.y, topLeft.y);
}

void Game::startLoop() {
	m_startTime = SDL_GetTicks();
}

void Game::handleEvents() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
					reshape();
				break;
			case SDL_QUIT:
				m_isRunning = false;
				break;
			case SDL_MOUSEBUTTONUP:
				printf("clic en (%d, %d) -> ", e.button.x, e.button.y);
				printf("(%f, %f)\n", Game::coordsSDLtoGL(e.button.x, e.button.y).x, Game::coordsSDLtoGL(e.button.x, e.button.y).y);
				c->handleClick(&e, Game::coordsSDLtoGL(e.button.x, e.button.y).x, Game::coordsSDLtoGL(e.button.x, e.button.y).y);
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == 1073741902)
					c = new Controller(true, MAP_SIZE);
				if (e.key.keysym.sym == SDLK_q)
					m_isRunning = false;
				if (e.key.keysym.sym == SDLK_n)
					c->m->nextTurn();
				break;
			default:
				c->handle(&e);
				break;
		}
	}
}

void Game::update() {
	c->update();
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
	/*else
		printf("Cannot follow framerate\n");*/
}

void Game::quit() {
	SDL_GL_DeleteContext(m_gl);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

int Game::getWindowWidth() {
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	return w;
}

int Game::getWindowHeight() {
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	return h;
}

Vector2d Game::coordsSDLtoGL(int x, int y) {
	return Game::coordsSDLtoGL(new Vector2i(x, y));
}

Vector2d Game::coordsSDLtoGL(Vector2i* v) {
	Vector2d res(0, 0);
	int sdlW = getWindowWidth();
	int sdlH = getWindowHeight();
	double ratio = sdlW / (double) sdlH;
	double glW = MAP_SIZE * ratio;
	double glH = MAP_SIZE;
	double glOffsetX = (glW - glH) / 2;
	res.x = v->x * glW / sdlW - glOffsetX;
	res.y = v->y * glH / sdlH;
	return res;
}

Vector2i Game::coordsGLtoSDL(double x, double y) {
	return Game::coordsGLtoSDL(new Vector2d(x, y));
}

Vector2i Game::coordsGLtoSDL(Vector2d* v) {
	Vector2i res(0, 0);
	int sdlW = getWindowWidth();
	int sdlH = getWindowHeight();
	double ratio = sdlW / (double) sdlH;
	double glW = MAP_SIZE / ratio;
	double glH = MAP_SIZE;
	double sdlOffsetX = (sdlW - sdlH) / 2;
	res.x = v->x * sdlW / glW + sdlOffsetX;
	res.y = v->y * sdlH / glW;
	return res;
}