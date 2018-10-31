#include "stdafx.h"
#include "Player.h"
#include "World.h"

Player::Player(string dirimg)
:Sprite(dirimg)
{
	score = 0;
}


Player::~Player()
{
}

void Player::moveUp()
{
		if (m_y < limitUp) {
			m_y = m_y + 0.0008;//mvSpeed
			setPosition(m_x, m_y);
		}
}

void Player::moveDown()
{
	if (m_y > limitDown) {
		m_y = m_y - 0.0008;//mvSpeed
		setPosition(m_x, m_y);
	}
}

void Player::addScore()
{
	score++;
}

int Player::getScore()
{
	return score;
}

void Player::setScore(int pScore) {
	score = pScore;
}