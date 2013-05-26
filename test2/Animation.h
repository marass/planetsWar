#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture &texture, char *name, int numberOfFrames, int startX, int startY, int sizeW, int sizeH, double frameTime, bool loop);
				/*
				*nazwa animacji
				*ilo�� klatek w animacji
				*wsp�rz�dne pierwszego sprite'a w atlasie
				*wysoko�� i szeroko�� jednej klatki
				*czas ramki
				*czy zap�tli�
				*/
	~Animation(void);

	void update(double dt);
	void setPos(double x, double y);
	void reset();
	bool isEnd();
	sf::Sprite &getSprite();

private:
	char *m_name;
	sf::Sprite m_sprite; //sprite
	int m_numberOfFrames;//ilo�� klatek
	int m_actualFrame;
	int m_startOnTexPosX;//pozycje startowe na teksturze
	int m_startOnTexPosY;
	int m_sizeOnTexW;//wymiary na teksturze
	int m_sizeOnTexH;
	double m_frameTime;
	bool m_loop;
	bool m_isEnd;
	double m_clock; //ile czasu up�yn�o
};

