#include "Engine.h"

Engine::~Engine(void)
{
	delete m_background;
	delete m_select;

	deleteStarsAndPaths();

	deleteShips();
	delete m_komp1;
}

void Engine::deleteStarsAndPaths()
{
	for(int i = 0; i < m_numberOfStars; i++)
	{
		delete m_stars[i];
	}

	for(int i = 0; i < m_numberOfStars; i++)
	{
		delete []m_pathsBetweenStars[i];
	}
	delete []m_pathsBetweenStars;//test
}

void Engine::deleteShips()
{
	Ships* tmp = m_shipsHead;
	if(tmp != NULL)
	{
		while(tmp->getNext() != NULL){
			tmp = tmp->getNext();
			if(tmp->getPrevious() != NULL)
			{
				delete tmp->getPrevious();
			}
		
		}
	}

	
}

void Engine::Load()
{
	srand(EngineLoadSeed);
	m_numberOfStars = 13;
	m_background = new Animation(Renderer::Get().getTexture("tlo"), "tlo", 1, 0, 0, 800, 600, 1, false) ;
	m_menuBackground = new Animation(Renderer::Get().getTexture("menu_tlo"), "menu_tlo", 1, 0, 0, 800, 600, 1, false) ;
	m_menuStartButton = new Animation(Renderer::Get().getTexture("start"), "startButton", 1, 0, 0, 300, 50, 1, false);
	m_menuStartButton->getSprite().setPosition(400 - 150, 300 - 25);
	m_select = new Animation(Renderer::Get().getTexture("zaznaczenie"), "czerwoneZaznaczenie", 1, 0, 0, 64, 64, 1, false) ;
	m_gameState = menu;
	//mapa i œcie¿ki //tmp
	
	m_stars = new StarNode*[m_numberOfStars];
	
	for(int i = 0; i < m_numberOfStars; i++)
	{
		m_stars[i] = new StarNode(i, rand() % (Renderer::Get().getWidth() - 64), rand() % (Renderer::Get().getHeight() - 64), 64, 64, rand() % 31 , 2 + (rand() % 25) / 10);
	}

	m_pathsBetweenStars = new bool*[m_numberOfStars];
	for(int i = 0; i < m_numberOfStars; i++)
	{
		m_pathsBetweenStars[i] = new bool[m_numberOfStars];
	}

	
	m_stars[0]->setNation(1);//player
	m_stars[m_numberOfStars - 1]->setNation(2);//komputer
	m_stars[m_numberOfStars - 3]->setNation(3);//komputer
	//m_stars[m_numberOfStars - 6]->setNation(4);//komputer
	/*m_stars[m_numberOfStars - 9]->setNation(5);//komputer
	m_stars[m_numberOfStars - 12]->setNation(6);//komputer*/

	for(int i = 0; i < m_numberOfStars; i++)
	{
		for(int j = i; j < m_numberOfStars; j++)
		{
			if(i == j ) continue;
			if(rand() % 100 < 20)
			{
				m_pathsBetweenStars[i][j] = true;
				m_pathsBetweenStars[j][i] = true;
			}
			else
			{
				m_pathsBetweenStars[i][j] = false;
				m_pathsBetweenStars[j][i] = false;
			}
		}
	}

	for(int i = 1; i < m_numberOfStars; i++)
	{
		bool tmp = false;
		for(int j = i + 1; j < m_numberOfStars; j++)
		{
			if(m_pathsBetweenStars[i][j])
			{
				tmp = true;
				break;
			}
		}
		if(!tmp)
		{
			m_pathsBetweenStars[i][i-1] = true;
			m_pathsBetweenStars[i-1][i] = true;
		}
	}

	m_selectedByPlayer = NULL;
	m_shipsHead = NULL;

	m_komp1 = (void**)new AI*[2];
	for(int i = 0; i < 2; i++)
	{
		m_komp1[i] = new AI(2 + i, m_stars, m_pathsBetweenStars, m_numberOfStars, &m_mutex);
	}
}

void Engine::update(double dt)
{
	if(m_gameState == game)
	{
		m_mutex.lock();

		for(int i = 0; i < m_numberOfStars; i++)
		{
			m_stars[i]->update(dt);
			if(m_stars[i]->canSend())
			{
				addShip(m_stars[i], m_stars[m_stars[i]->autoSend()]);
			}
		}

		if(m_selectedByPlayer != NULL)
		{
			m_select->setPos(m_selectedByPlayer->getPosX(), m_selectedByPlayer->getPosY());
		}
	
		Ships* tmp = m_shipsHead;
		while(tmp != NULL)
		{	
			Ships* tmp2 = tmp;
			while(tmp2 != NULL)
			{
				if(tmp->getPosX() + tmp->getWidth() < tmp2->getPosX() || tmp->getPosX() > tmp2->getPosX() + tmp2->getWidth() || tmp->getPosY() + tmp->getHeight() < tmp2->getPosY() || tmp->getPosY() > tmp2->getPosY() + tmp2->getHeight())
				{
					;
				}
				else
				{
					if(tmp->getNation() != tmp2->getNation() && tmp->getShips() > 0)
					{
						tmp->setShips(tmp2->attack(tmp->getShips()));
					}
				}
				tmp2 = tmp2->getNext();
			}
	
			if(tmp->getPosX() + tmp->getWidth() < m_stars[tmp->getDestination()]->getPosX() || tmp->getPosY() + tmp->getHeight() < m_stars[tmp->getDestination()]->getPosY() || tmp->getPosX() > m_stars[tmp->getDestination()]->getPosX()+m_stars[tmp->getDestination()]->getWidth() || tmp->getPosY() > m_stars[tmp->getDestination()]->getPosY()+m_stars[tmp->getDestination()]->getHeight() )
			{
				;//brak kolizji
			}
			else //kolizja
			{
				m_stars[tmp->getDestination()]->attack(tmp->getShips(), tmp->getNation());
				tmp->setShips(0);
			}
	
			if(tmp->getShips() > 0)
			{
				tmp->update(dt);
				tmp = tmp->getNext();	
			}
			else
			{
				if(tmp->getPrevious() == NULL)
				{
					m_shipsHead = tmp->getNext();
					delete tmp;
					tmp = m_shipsHead;
					if(tmp != NULL)
					{
						tmp->setPrevious(NULL);
					}
				}
				else
				{
					if(tmp->getNext() != NULL)
					{
						tmp = tmp->getPrevious();
					
						tmp->setNext(tmp->getNext()->getNext());
					
						delete tmp->getNext()->getPrevious();
	
						tmp->getNext()->setPrevious(tmp);
					}
					else
					{
						tmp->getPrevious()->setNext(NULL);
						delete tmp;
						tmp = NULL;
					}
				}
			}
		}
		
		m_mutex.unlock();
	}

}

void Engine::draw()
{
	if(m_gameState == game)
	{
		Renderer::Get().drawSprite(m_background->getSprite());
	
		for(int i = 0; i < m_numberOfStars; i++)
		{
			for(int j = i; j < m_numberOfStars; j++)
			{
				if(m_pathsBetweenStars[i][j])
				{
					Renderer::Get().drawLine(m_stars[i]->getPosX() + m_stars[i]->getWidth() /2, m_stars[i]->getPosY() + m_stars[i]->getHeight() /2, m_stars[j]->getPosX() + m_stars[j]->getWidth() /2, m_stars[j]->getPosY() + m_stars[j]->getHeight() /2, r, g, b);
				}
			}
			StarNode *tmp = m_stars[i];
			if(tmp->getSendDirection() != tmp->getNumber())
			{
				StarNode *dest = m_stars[tmp->getSendDirection()];
				double px = tmp->getPosX() + tmp->getWidth() /2;
				double py = tmp->getPosY() + tmp->getHeight() /2;
	
				double dx = (dest->getPosX() + dest->getWidth() /2) ;
				dx = dx - ((dx - px)/2);
				double dy = (dest->getPosY() + dest->getHeight() /2);
				dy = dy - ((dy - py)/2);
	
				Renderer::Get().drawLine(px, py, dx, dy, 0, 255, 0);
				Renderer::Get().drawLine(px-1, py, dx-1, dy, 0, 255, 0);
				Renderer::Get().drawLine(px+1, py, dx+1, dy, 0, 255, 0);
				Renderer::Get().drawLine(px, py-1, dx, dy-1, 0, 255, 0);
				Renderer::Get().drawLine(px, py+1, dx, dy+1, 0, 255, 0);
			}
		}
	
		for(int i = 0; i < m_numberOfStars; i++)
		{
			m_stars[i]->draw();
		}
	
		if(m_selectedByPlayer != NULL){
			Renderer::Get().drawSprite(m_select->getSprite());
		}
	
		Ships* tmp = m_shipsHead;
		while(tmp != NULL)
		{	
			tmp->draw();
			tmp = tmp->getNext();
		}
	}
	else if(m_gameState == menu)
	{
		Renderer::Get().drawSprite(m_background->getSprite());
		Renderer::Get().drawSprite(m_menuStartButton->getSprite());
	}

}
	
void Engine::leftClick(int x, int y)
{
	if(m_gameState == game)
	{
		//jeœli trwa gra:
		StarNode* tmp = clickOnStar(x, y);
		if(tmp == NULL)
		{
			m_selectedByPlayer = tmp;
		}
		else if(m_selectedByPlayer == NULL )
		{
			if(tmp->getNation() == 1)
			{
				m_selectedByPlayer = tmp;
			}
		}
		else if(m_selectedByPlayer != tmp)
		{
			addShip(m_selectedByPlayer, tmp);
			m_selectedByPlayer->setSendDirection(m_selectedByPlayer->getNumber());
			m_selectedByPlayer = NULL;
		}
		else if(m_selectedByPlayer == tmp)
		{
			m_selectedByPlayer->setSendDirection(m_selectedByPlayer->getNumber());
			m_selectedByPlayer = NULL;
		}
	}
	else if(m_gameState == menu)
	{
		int bx = m_menuStartButton->getSprite().getPosition().x;
		int by = m_menuStartButton->getSprite().getPosition().y;
		int w = m_menuStartButton->getSprite().getTextureRect().width;
		int h = m_menuStartButton->getSprite().getTextureRect().height;

		if(x < bx || x > bx + w || y < by || y > by + h) ;
		else
		{
			m_gameState = game;
		}
	}


}
	
void Engine::leftClickReleased(int x, int y)
{
	if(m_gameState == game)
	{
		if(m_selectedByPlayer != NULL)
		{
			StarNode* tmp = clickOnStar(x, y);
			if(tmp != NULL)
			{
				if(tmp != m_selectedByPlayer)
				{
					if(m_pathsBetweenStars[tmp->getNumber()][m_selectedByPlayer->getNumber()])
					{
						m_selectedByPlayer->setSendDirection(tmp->getNumber());
					}
					m_selectedByPlayer = NULL;
				}
			}
			
		}

	}
}

StarNode* Engine::clickOnStar(int x, int y)
{
	if(m_gameState == game)
	{
		for(int i = 0; i < m_numberOfStars; i++)
		{
			if(x < m_stars[i]->getPosX() || y < m_stars[i]->getPosY() || x > m_stars[i]->getPosX()+m_stars[i]->getWidth() || y > m_stars[i]->getPosY()+m_stars[i]->getHeight() )
			{
				continue;
			}
			else
			{
				//if(m_stars[i]->getNation() == 1)
				return m_stars[i];
			}
		}
	}
	return NULL;
}

/*sf::Mutex &Engine::getMutex()
{
	return m_mutex;
}*/

void Engine::addShip(StarNode* from, StarNode* to)
{
	if(m_gameState == game)
	{
		//sprawdz po³¹czenie
			if(m_pathsBetweenStars[from->getNumber()][to->getNumber()])
			{
				//wyœlij
				//m_mutex.lock();
				m_shipsHead = new Ships(from->getNumber(), to->getNumber(), from->getPosX() + from->getWidth()/2, from->getPosY() + from->getHeight()/2, 32, 32, from->getShips(), from->getNation(), to->getPosX() + to->getWidth()/2, to->getPosY() + to->getHeight()/2, m_shipsHead, NULL); 
				if(m_shipsHead->getNext() != NULL)
				{
					m_shipsHead->getNext()->setPrevious(m_shipsHead);
				}	
			//	m_mutex.unlock();
			}
	}

}


/*StarNode **Engine::getStarsHead()
{
	return m_stars;
}*/

void Engine::refreshPositions()
{
	//for(int i = 0; i < m_numberOfStars; i++);

}