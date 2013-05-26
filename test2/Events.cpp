#include "Events.h"

Events::Events(void)
{
	//m_oldMousePosX = 0;
	//m_oldMousePosY = 0;
	m_mousePress = false;
}

Events::~Events(void)
{
}

void Events::checkEvents()
{
	while(Renderer::Get().getWindow()->pollEvent(m_event))
    {
		// "close requested" event: we close the window
		if (m_event.type == sf::Event::Closed)
		{
			Renderer::Get().close();
			//Renderer::Get().getWindow()->close();
		}
		else if (m_event.type == sf::Event::Resized)
        {
			Renderer::Get().resize(m_event.size.width, m_event.size.height);
			Engine::Get().refreshPositions();
        }
		/*else if (m_event.type == sf::Event::KeyPressed)
        {
			if (m_event.key.code == sf::Keyboard::Right)
			{
				//Engine::Get().getCam()->moveCam(1, 0);
			}
			else if (m_event.key.code == sf::Keyboard::Left)
			{
				//Engine::Get().getCam()->moveCam(-1, 0);
			}
			else if (m_event.key.code == sf::Keyboard::Up)
			{
				//Engine::Get().getCam()->moveCam(0, -1);
			}
			else if (m_event.key.code == sf::Keyboard::Down)
			{
				//Engine::Get().getCam()->moveCam(0, 1);
			}
			else if (m_event.key.code == sf::Keyboard::R)
			{
				//Engine::Get().rotateStatics(2);
			}
			
        }*/
		else if(m_event.type == sf::Event::MouseButtonPressed)
		{
			m_mousePress = true;
			Engine::Get().leftClick(m_event.mouseButton.x, m_event.mouseButton.y);
		}
		else if(m_event.type == sf::Event::MouseButtonReleased)
		{
			if(m_mousePress) Engine::Get().leftClickReleased(m_event.mouseButton.x, m_event.mouseButton.y);
			m_mousePress = false;
		}
		/*else if(m_event.type == sf::Event::MouseMoved)
		{
			if(m_mousePress)
			{
				//	Engine::Get().getCam()->moveCam(-(m_event.mouseMove.x - m_oldMousePosX)/35.0f, -(m_event.mouseMove.y - m_oldMousePosY)/35.0f);
			}
			m_oldMousePosX = m_event.mouseMove.x;
			m_oldMousePosY = m_event.mouseMove.y;
		}*/
    }
}