#include "Object.h"

Object::~Object(void)
{
}

double Object::getPosX()
{
	return m_posX;
}

double Object::getPosY()
{
	return m_posY;
}

int Object::getWidth()
{
	return m_sizeW;
}

int Object::getHeight()
{
	return m_sizeH;
}
