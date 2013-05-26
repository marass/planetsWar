#pragma once
#include <SFML/System.hpp>
#include "Renderer.h"
#include "Animation.h"
#include "StarNode.h"
#include "Ships.h"
#include "AI.h"


const int EngineLoadSeed = 111111122;
const char r = 0;//sk³adowe do rysowania linii
const char g = 255;
const char b = 255;

enum gameStates
{
	menu = 0,
	game = 1,
	levels = 2,
};


class Engine
{
public:
	static Engine& Get()                                
	{
		static Engine Instance;
		return Instance;
	}
	~Engine(void);

	void Load();
	void update(double dt);
	void draw();
	void leftClick(int x, int y);
	void leftClickReleased(int x, int y);
	StarNode* clickOnStar(int x, int y);
	void deleteShips();
	void addShip(StarNode* from, StarNode* to);
	void deleteStarsAndPaths();
	//StarNode **getStarsHead();
	//sf::Mutex &getMutex();
	void refreshPositions();


private:
	int m_numberOfStars;
	Animation *m_background;
	Animation *m_menuStartButton;
	Animation *m_menuBackground;
	Animation *m_select;
	StarNode **m_stars;
	StarNode* m_selectedByPlayer;
	Ships* m_shipsHead;
	bool **m_pathsBetweenStars;
	void **m_komp1;
	sf::Mutex m_mutex;
	gameStates m_gameState;
	
};

