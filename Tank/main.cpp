#include "Controller/Controller.h"


#if defined WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
#else
int main()
#endif
{
    Client* client = Controller::startgui();
	if (client==NULL && !StartGui::isOfflineMode())
        return 0;

	Controller controller(700, 700, "Tank Battle");
	
    std::srand((unsigned)std::time(0));

    bool run = true;

	sf::Thread* thread = NULL;

	if (!StartGui::isOfflineMode()) {
		thread = new sf::Thread(std::bind(&recieveFromClient, controller.getView(), client, run));
		thread->launch();
	}

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
			controller.recieveEvents();
			sf::Event ev;
			while (controller.getEvent(ev))
            {
				if (ev.type == sf::Event::Closed)
                {
                    run = false;
					if (thread!=NULL) {
						thread->terminate();
						delete thread;
						client->shutDown();
					}
                }

				if(client!=NULL) {
					client->sendEventMessage(ev);
					wrt(client, controller.getWindow(), consoleText, console, ev, writeToConsole);
				}

            }

			controller.addText(consoleText);
			controller.refresh();
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
    return 0;
}