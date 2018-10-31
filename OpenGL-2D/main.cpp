#include "stdafx.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Player.h"
#include "World.h"
#include "Text.h"
#include "Projectile.h"
#include "Text.h"
#include <iostream>
#include "../3rd-party/freeglut3/include/GL/freeglut.h"
#include "AnimatedSprite.h"
#include "../3rd-party/SoundManager/SoundManager.h" //relative path to the main header
using namespace std;



int main(int argc, char** argv)
{
	//Sound
	clock_t startSoundtrack;
	double secondsPassed;
	SoundManager soundManager;
	SoundManager* pSoundManager = SoundManager::getInstance();
	pSoundManager->setVerbose(true);
	pSoundManager->createAudioObject("snd/soundtrack-01.wav");
	pSoundManager->createAudioObject("snd/cannon.wav");

	int audioObj1 = pSoundManager->getAudioObjectId("snd/soundtrack-01.wav");
	int audioObj2 = pSoundManager->getAudioObjectId("snd/cannon.wav");

	Renderer renderer;
	InputHandler inputHandler(renderer);
	renderer.initialize(argc, argv);
	Text2D *textInit = new Text2D("Presione cualquier tecla para empezar", -0.4, 0, 1);
	renderer.addObject(textInit);
	bool play = false;
	while (!play) {
		glutKeyboardFunc(inputHandler.__processPlay);
		if (inputHandler.doPlay()) {
			play = true;
			renderer.removeObject(textInit);
			pSoundManager->play(audioObj1, 1.f);
			startSoundtrack = clock();
		}
		glutMainLoopEvent();
		glutPostRedisplay();
		glutSwapBuffers();
	}
	inputHandler.initialize();
	Text2D *texto1 = new Text2D("PLAYER 1: 10", -0.75, 0.92, 1);
	Text2D *texto2 = new Text2D("PLAYER 2: 10", 0.40, 0.92, 1);
	Text2D *textWinner = new Text2D("GANADOR", -0.25, 0.5, 1);
	renderer.addObject(texto1);
	renderer.addObject(texto2);
	texto1->setName("text1");
	texto2->setName("text2");
	texto1->updateScore(0);
	texto2->updateScore(0);
	
	//background
	Sprite *bg = new Sprite("img/bg.jpg");
	bg->setDepth(2);
	renderer.addObject(bg);


	//test objects
	Player *pPlayer1= new Player("img/fighter-01.png");
	//Player1->setColor(255, 0, 0);
	pPlayer1->setPosition(-0.75, 0.0);
	pPlayer1->setRotation(270.0);
	pPlayer1->setSize(0.2);
	pPlayer1->setDepth(1.5);
	pPlayer1->setName("Player1");
	renderer.addObject(pPlayer1);

	Player *pPlayer2 = new Player("img/fighter-02.png");
	//pPlayer2->setColor(0, 255, 0);
	pPlayer2->setPosition(0.75, 0.0);
	pPlayer2->setRotation(90.0);
	pPlayer2->setSize(0.2);
	pPlayer2->setDepth(1.3);
	pPlayer2->setName("Player2");
	renderer.addObject(pPlayer2);
	//AnimatedSprite * pAnimatedSprite = new AnimatedSprite("img/fire-animation-2.png", 5, 2, true);
	//pAnimatedSprite->setSize(0.25);
	//renderer.addObject(pAnimatedSprite);

	while (1)
	{
		if (inputHandler.doPlay() == true) {

			secondsPassed = (clock() - startSoundtrack) / CLOCKS_PER_SEC;
			if (secondsPassed > 80) {
				startSoundtrack = clock();
				pSoundManager->play(audioObj1, 1.f);
			}
			//UPDATE////////////////////
			////////////////////////////
			//process queued events
			inputHandler.processEvents(pSoundManager, audioObj2);
			glutMainLoopEvent();

			//RENDER////////////////////
			////////////////////////////
			glutPostRedisplay();
			glutSwapBuffers();
		}

		if (pPlayer1->getScore() == 10) {
			textWinner->setText("Player 1 has won!!!");
			renderer.addObject(textWinner);
			inputHandler.stopPlaying();

			inputHandler.processEvents(pSoundManager, audioObj2);
			glutMainLoopEvent();

			glutPostRedisplay();
			glutSwapBuffers();
			play = false;
		}
		else if (pPlayer2->getScore() == 10)
		{
			textWinner->setText("Player 2 has won!!!");
			renderer.addObject(textWinner);
			inputHandler.stopPlaying();

			inputHandler.processEvents(pSoundManager, audioObj2);
			glutMainLoopEvent();

			glutPostRedisplay();
			glutSwapBuffers();
			play = false;
		}
		
		//Restart game
		if (!play) {
			Text2D *textRestart = new Text2D("Press any key to restart", -0.2, 0, 1);
			renderer.addObject(textRestart);
			while (!play) {
				glutKeyboardFunc(inputHandler.__processPlay);
				if (inputHandler.doPlay()) {
					play = true;

					renderer.removeObject(textRestart);
					inputHandler.initialize();
					pPlayer1->setScore(0);
					pPlayer2->setScore(0);
					texto1->updateScore(0);
					texto2->updateScore(0);
					renderer.removeObject(textWinner);
					pPlayer1->setPosition(-0.75, 0.5);
					pPlayer2->setPosition(0.75, -0.75);
				}
				glutMainLoopEvent();
				glutPostRedisplay();
				glutSwapBuffers();
			}
		}
	}
   
	return 0;
	
}
