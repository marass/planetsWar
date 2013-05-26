#pragma once
//#include <SFML/Window.hpp>
#include "Renderer.h"
#include "Engine.h"

class Events
{
public:
	Events(void);
	~Events(void);

	void checkEvents();

private:
	sf::Event m_event;
	//int m_oldMousePosX;
	//int m_oldMousePosY;
	bool m_mousePress;
};



