#include "Ships.h"


Ships::Ships(int from, int to, double x, double y, int sizeW, int sizeH, int numbersOfShips, int nation,  double destX, double destY, Ships* n, Ships* p) : Object(x - sizeW/2, y - sizeH/2, sizeW, sizeH)
{
	m_from = from;
	m_to = to;
	m_nation = nation;
	m_numberOfShips = numbersOfShips;
	m_animTravelShips = new Animation(Renderer::Get().getTexture("statki"), "ships1", 5, 0, 0, 32, 32, 0.3, true);
	m_next = n;
	m_previous = p;

	// 100px/1s

	double s = sqrt(pow(destX - x, 2) + pow(destY - y, 2)) ;//droga 
	double t = s / V;
	m_speedX = (destX - x) / t;
	m_speedY = (destY - y) / t;

}

Ships::~Ships(void)
{
	delete m_animTravelShips;
}

void Ships::update(double dt)
{
	m_posX += dt * m_speedX;
	m_posY += dt * m_speedY;

	m_animTravelShips->update(dt);

}

void Ships::draw()
{
	m_animTravelShips->setPos(m_posX, m_posY);
	Renderer::Get().drawSprite(m_animTravelShips->getSprite());
}

int Ships::getNation()
{
	return m_nation;
}

int Ships::attack(int ships)
{
	int tmp = m_numberOfShips;
	m_numberOfShips -= ships;
	return ships - tmp;
}

Ships* Ships::getNext()
{	
	return m_next;	
}

Ships* Ships::getPrevious()
{
	return m_previous;
}

int Ships::getShips()
{
	return m_numberOfShips;
}

void Ships::setShips(int ships)
{
	m_numberOfShips = ships;
}

int Ships::getDestination()
{
	return m_to;
}

void Ships::setNext(Ships* ship)
{
	m_next = ship;
}

void Ships::setPrevious(Ships* ship)
{
	m_previous = ship;
}
