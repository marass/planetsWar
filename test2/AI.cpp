#include "AI.h"

AI::AI(int nation, StarNode* stars_head[], bool *paths[], int numberOfStars, sf::Mutex *mutex)
	: m_thread(&AI::run, this)
{
	m_myNation = nation;
	m_starsHead = stars_head;
	m_paths = paths;
	m_numbersOfStars = numberOfStars;
	m_mutex = mutex;
	m_end = false;
	m_thread.launch();
}


AI::~AI(void)
{
}

void AI::run()
{
	while(!m_end)
	{
		sf::sleep(sf::seconds(5));
		StarNode *tmp ;//= m_starsHead[0];
		m_mutex->lock();
		for(int i = 0; i < m_numbersOfStars; i++)
		{
			tmp = m_starsHead[i] ;
			if(tmp->getNation() == m_myNation)
			{
				for(int j = 0; j < m_numbersOfStars; j++)
				{
					if(m_paths[i][j] == true && m_starsHead[j]->getNation() != m_myNation)
					{
						Engine::Get().addShip(tmp, m_starsHead[j]);
						break;
					}
					
				}
			}
			
		}
		m_mutex->unlock();//
	}
}
