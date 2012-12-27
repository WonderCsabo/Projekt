#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <exception>
#include <functional>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Graphics/View.h"
#include "Net/Client.h"
#include "GUI/StartGui.h"
#include "Util/DebugWindow.h"
#include "Util/GetInput.h"
#include "Util/Os.h"

Client* startgui()
{
    StartGui gui;
    return gui.getClient();
}

void addRandomBarrels(AbstractView* v)
{
    for(int i = 0; i< 50 ;i++)
    {
        v->addBarrel(std::rand()%700, std::rand()%700, (std::rand()%20+90)/100, (std::rand()%20+90)/100);
    }
}

#if defined WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
#else
int main()
#endif
{
    Client* client = startgui();
    if (client==NULL)
        return 0;

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(700,700), "Tank Battle!", sf::Style::Close);
    AbstractView* view = new View(window,true);//a második paramért a debugolás kiírásához van, alapértelmezetten hamis
    std::srand((unsigned)std::time(0));
    addRandomBarrels(view);

    bool run = true;

    sf::Thread thread(std::bind(&recieveFromClient, view, client, run));
    thread.launch();

    std::string console = "";
    sf::Text consoleText;
    consoleText.setCharacterSize(10);
    consoleText.setColor(sf::Color(255,255,255));
    sf::Vector2f pos(10, 10);
    consoleText.setPosition(pos);
    bool writeToConsole = false;

    while (window->isOpen())
    {
        try
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    run = false;
                    thread.terminate();
                    client->shutDown();
                    window->close();
                }

                client->sendEventMessage(event);
                wrt(client, window, consoleText, console, event, writeToConsole);

            }
            view->drawEverything();
            window->draw(consoleText);
            window->display();
            sf::sleep(sf::milliseconds(10));
        }
        catch(std::exception e)
        {
            e.what();
        }
    }

    if (client!=NULL) {
        client->shutDown();
        delete client;
    }

    delete window;

    return 0;
}