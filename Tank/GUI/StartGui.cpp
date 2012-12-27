#include "StartGui.h"

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

Client* StartGui::getClient()
{
	while(!isOK)
	{
		sf::sleep(sf::milliseconds(100));
	}
	window->close();
	return client;
}

void StartGui::loop()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->close();
				client = NULL;
				isOK = true;
			}
			sf::sleep(sf::milliseconds(10));

			panel->draw();

			GuiElement* clicked = panel->isClicked(event);
			if (clicked!=NULL && clicked->getType()==GuiElement::BTN)
			{
				if (clicked->getId()=="start") {
					client = new Client(strtoint(ePort->getText()), eIPAddress->getText(), eNickname->getText());
					if (!client->isConnected()) {
						delete client;
						client = NULL;
					}
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
	lPort = new Label("lport", window, new Coord(10,10), "Port:");
	lIPAddress = new Label("lipaddress", window, new Coord(10,40), "IP:");
	lNickname = new Label("lnickname", window, new Coord(10,70), "Nickname:");
	start = new Button("start", window, new Coord(10, 100), "Start client", 100, 25);
	ePort = new EditBox("eport", window, new Coord(80, 10), "54322", 150, 25);
	eIPAddress = new EditBox("eipaddress", window, new Coord(80, 40), "145.236.181.29", 150, 25);
	eNickname = new EditBox("enickname", window, new Coord(80, 70), "client0", 150, 25);
	panel->add(lPort);
	panel->add(lIPAddress);
	panel->add(lNickname);
	panel->add(start);
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