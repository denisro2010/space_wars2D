#include "stdafx.h"
#include "Sprite.h"
#include "../3rd-party/SOIL/src/SOIL.h"


Sprite::Sprite(string img)
{
	if (!img.empty())
	{
		m_dirimg = img;
		m_textureid = SOIL_load_OGL_texture(m_dirimg.c_str(), 0, 0, 0);
	}
	
}


Sprite::~Sprite()
{
}

void Sprite::setColor(float r, float g, float b)
{
	//When this method is called, we only store internally what this object's color will be
	//but, we need to pass the color to OpenGL every time the object is drawn
	m_r = r;
	m_g = g;
	m_b = b;
}

void Sprite::setPosition(double x, double y)
{
	//This method only updates internally the object's position. It still needs to be passed to OpenGL before drawing it
	m_x = x;
	m_y = y;
}

double Sprite::getX()
{
	return m_x;
}

double Sprite::getY()
{
	return m_y;
}

void Sprite::setDepth(double depth)
{
	//This method only updates internally the object's depth. It still needs to be passed to OpenGL before drawing it
	m_depth = depth;
}

void Sprite::setRotation(double angle)
{
	//This method only updates internally the object's rotation. It still needs to be passed to OpenGL before drawing it
	m_angle = angle;
}

void Sprite::setSize(double size)
{
	//This method only updates internally the object's size. It still needs to be passed to OpenGL before drawing it
	m_size = size;
}

double Sprite::getSize()
{
	return m_size;
}

void Sprite::draw()
{
	//TODO:

	//1. Pass the object's color to OpenGL

	//glColor3f(m_r, m_g, m_b);

	//2. Save the current transformation matrix

	glPushMatrix();

	//3. Set the transformation matrix of the quad using position, size and angle

	glTranslatef(m_x, m_y, 0); 
	glRotatef(m_angle, 0, 0, 1);
	glScalef(m_size, m_size, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureid);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//4. Draw the quad centered in [0,0] with coordinates: [-1,-1], [1,-1], [1,1] and [-1,1]

	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, -m_depth);

	glTexCoord2f(1, 1);
	glVertex3f(1, -1, -m_depth);

	glTexCoord2f(1, 0);
	glVertex3f(1, 1, -m_depth);

	glTexCoord2f(0, 0);
	glVertex3f(-1, 1, -m_depth);
	glEnd();

	//5. Restore the transformation matrix

	glPopMatrix();
}