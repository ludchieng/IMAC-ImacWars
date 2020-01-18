/*
 * Controller.cpp
 */

#include "Controller.h"

Controller::Controller() {
    m_view = new View();
    m_model = new Model();
    m_isRunning = true;
    m_player = NULL;
    this->playGame();
}

Controller::~Controller() {
    delete m_view;
    delete m_model;
}


void Controller::playGame() {
	//m_view->show(*m_model);
	m_model->moveUnit(m_model->getUnit(3, 3), 2, 1);
	cout << m_model->getUnit(2, 1)->getId() << endl;
}

void Controller::endGame() {

}
