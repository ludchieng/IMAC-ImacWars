/*
 * Game.cpp
 */

#include "Game.hpp"

const char Game::W_TITLE[] = "Imac Wars";
const float Game::GL_VIEW_SIZE = 200.;


Game::Game() {
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
		exit(600);

	SDL_Surface* m_surface;
	reshape(W_WIDTH, W_HEIGHT);
	SDL_WM_SetCaption(W_TITLE, NULL);
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

void Game::reshape(unsigned int width, unsigned int height) {
	SDL_Surface* tmp = SDL_SetVideoMode(   
		width, height, GL_BITS_PER_PIXEL,
		SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE
	);

	if(NULL == tmp)
		exit(601);
	
	m_surface = tmp;
	m_wRatio = width / (float) height;
	glViewport(0, 0, (m_surface)->w, (m_surface)->h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if( m_wRatio > 1) {
		gluOrtho2D(
		-GL_VIEW_SIZE / 2. * m_wRatio, GL_VIEW_SIZE / 2. * m_wRatio, 
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	} else {
		gluOrtho2D(
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / 2. / m_wRatio, GL_VIEW_SIZE / 2. / m_wRatio);
	}
}

void Game::handleEvents() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
			case SDL_QUIT:
				m_isRunning = false;
				break;
			case SDL_VIDEORESIZE:
				reshape(e.resize.w, e.resize.h);
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
	c->v->render(c);
	SDL_GL_SwapBuffers();
}

void Game::endLoop() {
	Uint32 elapsedTime = SDL_GetTicks() - m_startTime;
	if(elapsedTime < FRAMERATE_MILLISECONDS) 
		SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
}

void Game::quit() {
	SDL_Quit();
}