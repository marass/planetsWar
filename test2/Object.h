#pragma once
#include "Renderer.h"
#include "animation.h"

class Object
{
public:
	Object(double x, double y, int w, int h) : m_posX(x), m_posY(y), m_sizeW(w), m_sizeH(h) {} ;
	~Object(void);

	virtual void draw() = 0;
	virtual void update(double dt) = 0;

	double getPosX();
	double getPosY();
	int getWidth();
	int getHeight();

	void setPositions(double x, double y, int w, int h){m_posX = x; m_posY = y; m_sizeW = w; m_sizeH = h;};

protected:
	double m_posX;
	double m_posY;
	int m_sizeW;
	int m_sizeH;


};

