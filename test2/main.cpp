#include <SFML/Audio.hpp>

#include "Renderer.h"
#include "Engine.h"
#include "Animation.h"
#include "Events.h"
 
 int main()
 {
    // Create the main window
	Renderer::Get().Load(800, 600, "Start :)");
	Engine::Get().Load();
	Events events;
	sf::Clock mainClock;
	sf::Time mainLoopTime = sf::milliseconds(0);
	sf::Time oneFrameTime = sf::milliseconds(0);
	sf::Time toUpdateEngineTime = sf::milliseconds(20);
	int FPS = 0;
	sf::Time fpsTime = sf::milliseconds(0);
    
	sf::Text text("Hello SFML", Renderer::Get().getFont("unreal"), 50);
 
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("data/musics/scale_c7.wav"))
        return 1;

    // Play the music
    music.play();
	
	
    while (Renderer::Get().windowIsOpen())
    {
		events.checkEvents();
		oneFrameTime = mainClock.restart();
		mainLoopTime += oneFrameTime;
		fpsTime += oneFrameTime;

		//FPS
		FPS++;
		if(fpsTime >= sf::seconds(1))
		{
			char title[250];
			sprintf( title, "Liczba FPS: %d  Rozmiar: %d X %d", FPS, Renderer::Get().getWidth(), Renderer::Get().getHeight());
			Renderer::Get().getWindow()->setTitle(title);

			FPS = 0;
			fpsTime = sf::milliseconds(0);
		}
		
		while(mainLoopTime >= toUpdateEngineTime)
		{
			Engine::Get().update((double)toUpdateEngineTime.asSeconds());
			mainLoopTime -= toUpdateEngineTime;
		}
		
		Renderer::Get().getWindow()->clear();
		Engine::Get().draw();
		Renderer::Get().getWindow()->draw(text);
		Renderer::Get().draw();
    }
 
     return 0;
 }