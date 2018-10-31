#include "stdafx.h"
#include "InputHandler.h"
#include "World.h"
#include "Projectile.h"
#include "Renderer.h"
#include "../3rd-party/freeglut3/include/GL/freeglut.h"
#include "AnimatedSprite.h"


InputHandler* InputHandler::m_pInputHandler = nullptr;
double secondsToDelay = 0.1;
clock_t startTimeP1 = clock();
clock_t startTimeP2 = clock();
double secondsPassed;

InputHandler::InputHandler(Renderer& renderer): m_renderer(renderer)
{
	m_pInputHandler = this;
}


InputHandler::~InputHandler()
{
}

void InputHandler::initialize()
{
	//glutKeyboardFunc(__processPlay);
	glutKeyboardFunc(__processKeyboard);
	//TODO glutKeyboardUpFunc deje de moverse cuando se suelte y que detecte cuando pulsado con booleans
	glutKeyboardUpFunc(__processUpKeyboard);

}


void InputHandler::processKeyboard(unsigned char key, int x, int y)
{
	if (playing == true) {
		//keyboard callback function
		Renderer* renderer = (Renderer*)Renderer::get();

		player2 = (Player*)Renderer::get()->getObject("Player2");
		player1 = (Player*)Renderer::get()->getObject("Player1");

		switch (key) {
			//TODO
		case '8':
			mvUp2 = true; break;
		case '2':
			mvDwn2 = true; break;
		case '4':
			retard(player2, renderer, false);
			break;

		case 'w':
			mvUp1 = true; break;
		case 's':
			mvDwn1 = true; break;
		case 'd':
			retard(player1, renderer, true);
			break;

		case 27: exit(0);
		}
	}
}

void InputHandler::processUpKeyboard(unsigned char key, int x, int y) {
	//keyboard callback function
	Renderer* renderer = (Renderer*)Renderer::get();
	
	player2 = (Player*)Renderer::get()->getObject("Player2");
	player1 = (Player*)Renderer::get()->getObject("Player1");
	if (playing == true) {
		switch (key)
		{
			//TODO
		case '8':
			mvUp2 = false; break;
		case '2':
			mvDwn2 = false; break;
		case '4':
			retard(player2, renderer, false);
			break;

		case 'w':
			mvUp1 = false; break;
		case 's':
			mvDwn1 = false; break;
		case 'd':
			retard(player1, renderer, true);
			break;

		case 27: exit(0);
		}
	}
}

void InputHandler::processPlay(unsigned char key, int x, int y) {

	switch (key) {
		//TODO		
	case 27: exit(0);
	default: playing = true; break;
	}
}

void InputHandler::retard(Player* player, Renderer* renderer, bool direction) {
	clock_t startTimePl;
	if (direction) {
		startTimePl = startTimeP1;
	}else {
		startTimePl = startTimeP2;
	}
	secondsPassed = (clock() - startTimePl) / CLOCKS_PER_SEC;
	if (secondsPassed >= secondsToDelay)
	{
		renderer->addObject(new Projectile(player->getX(), player->getY(), direction, "img/fire-animation-2.png"));
	
		if (direction) {
			shoot1 = true;
			startTimeP1 = clock();
		}
		else {
			shoot2 = true;
			startTimeP2 = clock();
		}
	}
}

void InputHandler::__processKeyboard(unsigned char key, int x, int y)
{
	if (m_pInputHandler)
		m_pInputHandler->processKeyboard(key, x, y);
}

void InputHandler::__processUpKeyboard(unsigned char key, int x, int y) {
	if (m_pInputHandler)
		m_pInputHandler->processUpKeyboard(key, x, y);
}

void InputHandler::processEvents(SoundManager* pSoundManager, int cannon) {
	if (mvUp1) {
		player1->moveUp();
	}
	if (mvUp2) {
		player2->moveUp();
	}
	if (mvDwn1) {
		player1->moveDown();
	}
	if (mvDwn2) {
		player2->moveDown();
	}
	if (shoot1) {
		pSoundManager->play(cannon, 0.5f - 1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
		shoot1 = false;
	}
	if (shoot2) {
		pSoundManager->play(cannon, 0.5f - 1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
		shoot2 = false;
	}
}

bool InputHandler::doPlay() {
	return playing;
}

void InputHandler::stopPlaying() {
	playing = false;
	mvUp1 = false;
	mvUp2 = false;
	mvDwn1 = false;
	mvDwn2 = false;
}

void InputHandler::__processPlay(unsigned char key, int x, int y) {
	if (m_pInputHandler) {
		m_pInputHandler->processPlay(key, x, y);
	}
}
