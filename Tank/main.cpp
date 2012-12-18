#include <SFML/Graphics.hpp>
#include "View.h"
#include <exception>
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