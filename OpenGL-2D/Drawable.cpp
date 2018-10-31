#include "Drawable.h"
#include "Projectile.h"

string Drawable::getName() {
	return name;
}

void Drawable::setName(string pName){
	name = pName;
}

void Drawable::markForDeletion()
{
	m_alive = false;
}

bool Drawable::isAlive()
{
	return m_alive;
}

/*
bool Drawable::canBeHit(Drawable* obj)
{
	if (typeid(obj) == typeid(new Projectile(0, 0, true)))
		return true;
	else return false;
}
*/