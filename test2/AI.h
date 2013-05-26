#pragma once
#include <SFML/System.hpp>
#include "StarNode.h"
#include "Ships.h"
#include "Engine.h"

class AI
{
public:
	AI(int nation, StarNode* stars_head[], bool *paths[], int numberOfStars, sf::Mutex *mutex );
	~AI(void);

	void run();


private:
	StarNode **m_starsHead;
	bool **m_paths;
	int m_numbersOfStars;
	sf::Mutex *m_mutex;
	bool m_end;
	int m_myNation;
	sf::Thread m_thread;
};

