#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <functional>
#include "Controller.h"
#include "Graphics/View.h"
#include "Net/Client.h"
#include "GUI/StartGui.h"
#include "Util/DebugWindow.h"
#include "Util/GetInput.h"
#include "Util/Os.h"








#if defined WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
#else
int main()
#endif
{
	Controller controller(700, 700, "Tank Battle");
   /* Client* client = controller.startgui();
    if (client==NULL)
        return 0;*/

	
    std::srand((unsigned)std::time(0));

    bool run = true;

	/*sf::Thread thread(std::bind(&recieveFromClient, controller.getView(), client, run));
    thread.launch();*/

    std::string console = "";
    sf::Text consoleText;
    consoleText.setCharacterSize(10);
    consoleText.setColor(sf::Color(255,255,255));
    sf::Vector2f pos(10, 10);
    consoleText.setPosition(pos);
    bool writeToConsole = false;

	while (controller.programRunning())
    {
        try
        {
            while (controller.pollEvent())
            {
				if (controller.getEvent().type == sf::Event::Closed)
                {
                    run = false;
                    /*thread.terminate();
                    client->shutDown();*/
                }

                /*client->sendEventMessage(controller.getEvent());
				wrt(client, controller.getWindow(), consoleText, console, controller.getEvent(), writeToConsole);*/

            }

			controller.addText(consoleText);
			controller.refresh();
        }
        catch(std::exception e)
        {
            e.what();
        }

    }

    /*if (client!=NULL) {
        client->shutDown();
        delete client;
    }*/
    return 0;
}