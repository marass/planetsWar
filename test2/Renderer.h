#pragma once
#include <SFML/Graphics.hpp>

struct nodeTexture
{
	char *m_name;
	sf::Texture m_texture;
	nodeTexture *m_next;
	nodeTexture(char *name, const char *path)
	{
		m_name = name;
		if(!m_texture.loadFromFile(path)) 
		{
			exit(1);//error
		}
		m_next = NULL;
	}
};

struct nodeFont
{
	char *m_name;
	sf::Font m_font;
	nodeFont *m_next;
	nodeFont(char *name, const char *path)
	{
		m_name = name;
		if(!m_font.loadFromFile(path)) 
		{
			exit(1);//error
		}
		m_next = NULL;
	}
};

class Renderer
{
public:
	static Renderer& Get()                                
	{
		static Renderer Instance;
		return Instance;
	}
	~Renderer(void);

	void Load(int width, int height, const char *t);
	void resize(int width, int height);
	int getWidth();
	int getHeight();
	sf::RenderWindow *getWindow();
	bool windowIsOpen();
	void draw();
	void close();
	void drawSprite(sf::Sprite &sprite);
	void drawLine(double xa, double ya, double xb, double yb, char r, char g, char b);
	sf::Texture &getTexture(char *name);
	sf::Font &getFont(char *name);

private:
	sf::RenderWindow m_window;
	int m_width;
	int m_height;
	nodeTexture *m_allTexturesHead;
	nodeFont *m_allFontsHead;
};

