#pragma once
#include <string>
using namespace std;

class Drawable
{
	bool m_alive= true;
	string name;
public:
	virtual void draw() = 0;
	string getName();
	void setName(string name);

	void markForDeletion();
	bool isAlive();
	bool canBeHit(Drawable * obj);
};