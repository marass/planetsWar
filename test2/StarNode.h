#pragma once
#include "object.h"
#include "Animation.h"
//#include "Engine.h"

const int numberOfStates = 3;

enum starStates
{
	base = 0,
	newNation = 1,
	battle = 2,
};

class StarNode :
	public Object
{
public:
	StarNode(int number, double x, double y, int w, int h, int numberOfShips, double incrementPerSecond);
	~StarNode(void);

	void update(double dt);
	void draw();
	void attack(int ships, int nation);
	void addShips(int ships);
	int getNation();
	int getShips();
	void setNation(int nation);
	int getNumber();
	void setSendDirection(int number);
	bool canSend();
	int getSendDirection();
	int autoSend();

private:
	int m_numberOnMap;
	int m_directionToSend;
	double m_numberOfShips;
	double m_incrementPerSecond;
	double m_autoSendTimer;
	double m_autoSendTime; //czas co ile wysy³aæ statki
	starStates m_state;
	bool m_hasChangeNation;
	int m_nation;
	Animation *m_anims[numberOfStates];
	sf::Text m_textShips;
	sf::Text m_textIncrement;
	sf::Text m_textNation;
};

