#include "StarNode.h"

char buff[10];
StarNode::StarNode(int number, double x, double y, int w, int h, int numberOfShips, double incrementPerSecond) : Object(x, y, w, h)
{
	m_numberOnMap = number;
	m_directionToSend = number;
	m_numberOfShips = numberOfShips;
	m_incrementPerSecond = incrementPerSecond;
	m_state = battle;

	m_hasChangeNation = true;
	m_nation = 0;
	
	m_anims[base] = new Animation(Renderer::Get().getTexture("StarNode"), "base", 10, 0, 0, 64, 64, 0.1, true);
	m_anims[base]->getSprite().setPosition(x, y);
	m_anims[newNation] = new Animation(Renderer::Get().getTexture("StarNode"), "newNation", 5, 0, 64, 64, 64, 0.1, false);
	m_anims[newNation]->getSprite().setPosition(x, y);
	m_anims[battle] =  new Animation(Renderer::Get().getTexture("StarNode"), "battle", 5, 0, 128, 64, 64, 0.1, false);
	m_anims[battle]->getSprite().setPosition(x, y);

	
	m_textShips.setFont(Renderer::Get().getFont("unreal"));
	m_textShips.setColor(sf::Color(0, 255, 0));
	m_textShips.setPosition(x + w/2 - 10, y + h/2 - 20);
	m_textShips.setCharacterSize(15);
	m_textShips.setString(itoa(numberOfShips, buff, 10));

	m_textIncrement.setFont(Renderer::Get().getFont("unreal"));
	m_textIncrement.setColor(sf::Color(0, 0, 255));
	m_textIncrement.setPosition(x + w/2 - 10, y + h/2 - 5);
	m_textIncrement.setCharacterSize(15);
	m_textIncrement.setString(itoa((int)(incrementPerSecond*10), buff, 10));

	m_textNation.setFont(Renderer::Get().getFont("unreal"));
	m_textNation.setColor(sf::Color(255, 0, 0));
	m_textNation.setPosition(x + w/2 - 10, y + h/2 + 10);
	m_textNation.setCharacterSize(15);
	m_textNation.setString(itoa(m_nation, buff, 10));

	m_autoSendTime = 5;
	m_autoSendTimer = 0;
}


StarNode::~StarNode(void)
{
	delete m_anims[base];
	delete m_anims[newNation];
	delete m_anims[battle];
}

void StarNode::update(double dt)
{
	switch(m_state)
	{
	case base:
		if(m_nation > 0)
		{
			if(m_directionToSend != m_numberOnMap) m_autoSendTimer += dt;
			else m_autoSendTimer = 0;

			m_numberOfShips += m_incrementPerSecond * dt;//mo¿e wyskoczyæ poza inta
			m_textShips.setString(itoa((int)m_numberOfShips, buff, 10));
		}
		break;

	case newNation:
		if(m_anims[newNation]->isEnd())
		{
			m_anims[newNation]->reset();
			m_state = base;
			
		}
		break;

	case battle:
		if(m_anims[battle]->isEnd())
		{
			m_anims[battle]->reset();
			m_state = base;

			if(m_hasChangeNation)
			{
				m_state = newNation;
				m_hasChangeNation = false;
				m_textNation.setString(itoa((int)m_nation, buff, 10));
				setSendDirection(m_numberOnMap);
			}
		}
		
		
		break;

	default:
		break;//error
	}

	m_anims[m_state]->update(dt);
}

void StarNode::draw()
{
	Renderer::Get().drawSprite(m_anims[m_state]->getSprite());
	Renderer::Get().getWindow()->draw(m_textShips);
	Renderer::Get().getWindow()->draw(m_textIncrement);
	Renderer::Get().getWindow()->draw(m_textNation);
}

int StarNode::getShips()
{
	m_numberOfShips /= 2;
	m_textShips.setString(itoa((int)m_numberOfShips, buff, 10));
	return (int)m_numberOfShips;
}

void StarNode::addShips(int ships)
{
	m_numberOfShips += ships;
}

int StarNode::getNation()
{
	return m_nation;
}

void StarNode::attack(int ships, int nation)
{
	if(nation != m_nation)
	{
		m_state = battle;
		m_anims[battle]->reset();
		if(m_numberOfShips > ships)
		{
			m_numberOfShips -= ships;
		}
		else
		{
			m_numberOfShips = ships - m_numberOfShips;
			m_hasChangeNation = true;
			m_nation = nation;
		}
	}
	else
	{
		addShips(ships);
	}
	m_textShips.setString(itoa((int)m_numberOfShips, buff, 10));
	
}

void StarNode::setNation(int nation)
{
	m_nation = nation;
	m_textNation.setString(itoa(m_nation, buff, 10));
}

int StarNode::getNumber()
{
	return m_numberOnMap;
}

void StarNode::setSendDirection(int number)
{
	m_directionToSend = number;
}

bool StarNode::canSend()
{
	if(m_autoSendTimer >= m_autoSendTime)
	{
		return true;
	}
	return false;
}

int StarNode::getSendDirection()
{
	//m_autoSendTimer -= m_autoSendTime;
	return m_directionToSend;
}

int StarNode::autoSend()
{
	m_autoSendTimer -= m_autoSendTime;
	return m_directionToSend;
}