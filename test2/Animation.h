#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture &texture, char *name, int numberOfFrames, int startX, int startY, int sizeW, int sizeH, double frameTime, bool loop);
				/*
				*nazwa animacji
				*iloœæ klatek w animacji
				*wspó³rzêdne pierwszego sprite'a w atlasie
				*wysokoœæ i szerokoœæ jednej klatki
				*czas ramki
				*czy zapêtliæ
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
	int m_numberOfFrames;//iloœæ klatek
	int m_actualFrame;
	int m_startOnTexPosX;//pozycje startowe na teksturze
	int m_startOnTexPosY;
	int m_sizeOnTexW;//wymiary na teksturze
	int m_sizeOnTexH;
	double m_frameTime;
	bool m_loop;
	bool m_isEnd;
	double m_clock; //ile czasu up³ynê³o
};

