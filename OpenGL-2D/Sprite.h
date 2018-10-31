#pragma once

#include "Drawable.h"

class Sprite: public Drawable
{
protected:
	float m_r, m_g, m_b;
	
	protected:double m_x= 0.0, m_y= 0.0; //position around which the quad is drawn
	protected: string m_dirimg;
	protected: int m_textureid;
	double m_depth = 1.0; // the renderer draws depths in range [1.0,20.0]

	double m_size= 1.0; //size of the quad

	double m_angle= 0.0; //rotation angle

public:
	Sprite(string img);
	~Sprite();

	virtual void draw();
	void setColor(float r, float g, float b);
	void setPosition(double x, double y);
	void setDepth(double depth);
	void setRotation(double angle);
	void setSize(double size);
	double getSize();
	double Sprite::getX();
	double Sprite::getY();
};

