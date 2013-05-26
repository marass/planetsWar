#include "Animation.h"


Animation::Animation(sf::Texture &texture, char *name, int numberOfFrames, int startX, int startY, int sizeW, int sizeH, double frameTime, bool loop)
{
	m_name = name;
	m_numberOfFrames = numberOfFrames;
	m_actualFrame = 0;
	m_startOnTexPosX = startX;
	m_startOnTexPosY = startY;
	m_sizeOnTexW = sizeW;
	m_sizeOnTexH = sizeH;
	m_frameTime = frameTime;
	m_loop = loop;
	m_clock = 0;
	m_isEnd = false;
	

	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(sf::IntRect(startX, startY, sizeW, sizeH));
	m_sprite.setPosition(0, 0);
}


Animation::~Animation(void)
{
}

void Animation::update(double dt)
{
	m_clock += dt;
	
	while(m_clock >= m_frameTime){
		if(m_actualFrame < m_numberOfFrames - 1)
		{
			m_actualFrame++;
		}
		else if(m_loop)
		{
			m_actualFrame = 0;
		}
		else
		{
			m_isEnd = true;
		}
		m_clock -= m_frameTime;
		m_sprite.setTextureRect(sf::IntRect(m_startOnTexPosX + m_actualFrame * m_sizeOnTexW, m_startOnTexPosY, m_sizeOnTexW, m_sizeOnTexH));
		
	}

}

void Animation::setPos(double x, double y)
{
	m_sprite.setPosition((float)x, (float)y);
}

void Animation::reset()
{
	m_actualFrame = 0;
	m_clock = 0;
	m_isEnd = false;
	m_sprite.setTextureRect(sf::IntRect(m_startOnTexPosX + m_actualFrame * m_sizeOnTexW, m_startOnTexPosY, m_sizeOnTexW, m_sizeOnTexH));
}

sf::Sprite &Animation::getSprite()
{
	return m_sprite;
}

bool Animation::isEnd()
{
	return m_isEnd;;
}