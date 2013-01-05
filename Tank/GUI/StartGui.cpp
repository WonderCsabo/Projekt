#include "StartGui.h"
#include "../Util/DebugWindow.h"

bool StartGui::offlineMode = false;

StartGui::StartGui()
{
	window = new sf::RenderWindow(sf::VideoMode(400, 400), "Set up connection", sf::Style::Close);
	makeGui();
	isOK = false;
	loop();
}

StartGui::~StartGui()
{
	delete window;
	delete panel;
}

bool StartGui::isOfflineMode()
{
	return StartGui::offlineMode;
}

Client* StartGui::getClient()
{
	while(!isOK)
	{
		sf::sleep(sf::milliseconds(100));
	}
	window->close();
	return client;
}

void StartGui::tryToConnect()
{
	client = new Client(strtoint(ePort->getText()), eIPAddress->getText(), eNickname->getText());
	if (!client->isConnected())
	{
		delete client;
		client = NULL;
	}
	isOK = true;
}

void StartGui::loop()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				client = NULL;
				isOK = true;
			}
			sf::sleep(sf::milliseconds(10));

			panel->draw();

			GuiElement* clicked = panel->isClicked(event);
			if (clicked!=NULL && clicked->getType()==GuiElement::BTN)
			{
				if (clicked->getId()=="start")
				{
					sf::Thread connectionThread(&StartGui::tryToConnect, this);//tryToConnect();
					connectionThread.launch();
				}
				else if (clicked->getId()=="offline")
				{
					std::cout << "offlinemode\n";
					std::cout << client << std::endl;
					//if (client!=NULL) {
					//	delete client;
					//}
					client = NULL;
					offlineMode = true;
					isOK = true;
				}
			}
			panel->type(event);
		}
		if (isOK) break;
		sf::sleep(sf::milliseconds(10));
	}
}

void StartGui::makeGui()
{
	//init gui
	panel = new GuiContainer(window);
	Coord lportcoord(10, 10);
	lPort = new Label("lport", window, lportcoord, "Port:");
	Coord lipcoord(10, 40);
	lIPAddress = new Label("lipaddress", window, lipcoord, "IP:");
	Coord lnickcoord(10, 70);
	lNickname = new Label("lnickname", window, lnickcoord, "Nickname:");
	Coord startcoord(10, 100);
	start = new Button("start", window, startcoord, "Start client", 100, 25);
	Coord offlinecoord(120, 100);
	offline = new Button("offline", window, offlinecoord, "Offline mode", 100, 25);
	Coord eportcoord(80, 10);
	ePort = new EditBox("eport", window, eportcoord, "54322", 150, 25);
	Coord eipcoord(80, 40);
	eIPAddress = new EditBox("eipaddress", window, eipcoord, "80.98.222.28", 150, 25);
	Coord enickcoord(80, 70);
	eNickname = new EditBox("enickname", window, enickcoord, "client0", 150, 25);
	panel->add(lPort);
	panel->add(lIPAddress);
	panel->add(lNickname);
	panel->add(start);
	panel->add(offline);
	panel->add(ePort);
	panel->add(eIPAddress);
	panel->add(eNickname);
}

int StartGui::strtoint(std::string s)
{
	std::stringstream ss(s);
	int ret;
	ss >> ret;
	return ret;
}
