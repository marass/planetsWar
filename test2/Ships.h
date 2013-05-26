#pragma once
#include "Object.h"
#include "Animation.h"

const int V = 100;

class Ships : 
	public Object
{
public:
	Ships(int from, int to, double x, double y, int sizeW, int sizeH, int numbersOfShips, int nation, double destX, double destY, Ships* n, Ships* p);
	~Ships(void);
	void update(double dt);
	void draw();
	int getNation();
	int getShips();
	int getDestination();
	void setShips(int ships);
	int attack(int ships);
	Ships* getNext();
	Ships* getPrevious();
	void setNext(Ships* ship);
	void setPrevious(Ships* ship);

private:
	int m_numberOfShips;
	double m_speedX;
	double m_speedY;
	int m_from;
	int m_to;
	int m_nation;
	Animation* m_animTravelShips;

	Ships* m_next;
	Ships* m_previous;
};

