#include "Renderer.h"

Renderer::~Renderer()
{
	nodeTexture *tmp;
	while(m_allTexturesHead != NULL)
	{
		tmp = m_allTexturesHead;
		m_allTexturesHead = m_allTexturesHead->m_next;
		delete tmp;
	}

	nodeFont *tmp2;
	while(m_allFontsHead != NULL)
	{
		tmp2 = m_allFontsHead;
		m_allFontsHead = m_allFontsHead->m_next;
		delete tmp2;
	}

}

sf::RenderWindow *Renderer::getWindow()
{
	return &m_window;
}

void Renderer::Load(int width, int height, const char *t)
{
	m_window.create(sf::VideoMode(width, height), t, sf::Style::Default);
	m_window.setVerticalSyncEnabled(true);

	m_width = width;
	m_height = height;

	//³adowanie tekstur
	m_allTexturesHead = new nodeTexture("tlo", "data/images/universe.jpg");
	nodeTexture *tmp = m_allTexturesHead;
	tmp->m_next = new nodeTexture("zaznaczenie", "data/images/zaznaczenie.png");
	tmp = tmp->m_next;
	tmp->m_next = new nodeTexture("StarNode", "data/images/starNode.png");
	tmp = tmp->m_next;
	tmp->m_next = new nodeTexture("statki", "data/images/statki.png");
	tmp = tmp->m_next;
	tmp->m_next = new nodeTexture("start", "data/images/start.png");
	tmp = tmp->m_next;
	tmp->m_next = new nodeTexture("menu_tlo", "data/images/universe.jpg");
	tmp = tmp->m_next;
	//itd;

	//³adowanie fontów
	m_allFontsHead = new nodeFont("unreal", "data/UnrealT.ttf");
	nodeFont *tmp2 = m_allFontsHead;

}

void Renderer::resize(int width, int height)
{
	m_window.setSize(sf::Vector2u(width, height));
	m_width = width;
	m_height = height;
}

int Renderer::getWidth()
{
	return m_width;
}

int Renderer::getHeight()
{
	return m_height;
}

bool Renderer::windowIsOpen()
{
	return m_window.isOpen();
}

void Renderer::close()
{
	m_window.close();
}

void Renderer::drawSprite(sf::Sprite &sprite)
{
	m_window.draw(sprite);
}

void Renderer::draw()
{
	m_window.display();
}

sf::Texture &Renderer::getTexture(char *name)
{
	nodeTexture *tmp = m_allTexturesHead;
	while(tmp != NULL)
	{
		if(name == tmp->m_name)
		{
			return tmp->m_texture;
		}
		tmp = tmp->m_next;
	}
	return m_allTexturesHead->m_texture;//error
}

sf::Font &Renderer::getFont(char *name)
{
	nodeFont *tmp = m_allFontsHead;
	while(tmp != NULL)
	{
		if(name == tmp->m_name)
		{
			return tmp->m_font;
		}
		tmp = tmp->m_next;
	}
	return m_allFontsHead->m_font;//error
}

void Renderer::drawLine(double xa, double ya, double xb, double yb, char r, char g, char b)
{
	sf::Vertex line[2] = {sf::Vector2f(xa, ya), sf::Vector2f(xb, yb)};
	line[0].color = sf::Color(r, g, b);
	line[1].color = sf::Color(r, g, b);
	m_window.draw(line, 2, sf::Lines);
}
