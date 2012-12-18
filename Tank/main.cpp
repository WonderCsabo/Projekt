#include <SFML/Graphics.hpp>
#include "View.h"
#include <exception>
<<<<<<< HEAD
#include <vector>
void __stdcall WinMain(int a, short d, char * c, char* b) {
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(700,700), "Tank Battle!");
    AbstractView *view = new View(window,true);//a második paramért a debugolás kiírásához van, alapértelmezetten hamis
    std::vector<Coordinate*> blocks;
    srand((unsigned)time(0));
    int blocksCount = 20+rand()%20;
    for(int i = 0; i < blocksCount; i++) {
        blocks.push_back(new Coordinate(rand()%700,rand()%700));
    }
    view->addBlocks(blocks);
    while (window->isOpen()) {
        try {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
            }
            view->drawEverything();
        } catch(std::exception e) {
            view->addDebugInfo(e.what());
        }
    }
    for(int i = 0; i < blocksCount; i++) delete blocks[i];
    delete view;
	//delete window;
    return;
}
=======
#include <vector> 
void __stdcall WinMain(int a, short d, char * c, char* b)
{
	
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(700,700), "Tank Battle!");
	AbstractView *view = new View(window,true);//a második paramért a debugolás kiírásához van, alapértelmezetten hamis
		while (window->isOpen())
		{
			try 
			{
				sf::Event event;
				while (window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window->close();
				}
				view->addDebugInfo("Debug info1");
				view->addDebugInfo("Debug info2");
				view->drawEverything();
			}
			catch(std::exception e)
			{
				e.what();
			}
		}
	

    return ;
}
>>>>>>> parent of 9167709... AkadÃ¡lyok hozzÃ¡adva
