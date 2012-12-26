#pragma once
#ifndef STARTGUI_HPP
#define STARTGUI_HPP

#include <SFML/Graphics.hpp>
#include "Net/Client.h"
#include "GuiContainer.hpp"

class StartGui
{
public:
	StartGui()
	{
		window = new sf::RenderWindow(sf::VideoMode(400, 400), "Set up connection", sf::Style::Close);
		makeGui();
		isOK = false;
		loop();
	}

	Client* getClient()
	{
		while(!isOK)
		{
			sf::sleep(sf::milliseconds(100));
		}
		window->close();
		return client;
	}

	~StartGui()
	{
		delete window;
		delete panel;
	}

private:
	GuiContainer* panel;
	Label* lPort;
	Label* lIPAddress;
	Label* lNickname;
	//Label* lDebug;
	Button* start;
	//Button* send;
	EditBox* ePort;
	EditBox* eIPAddress;
	EditBox* eNickname;
	//EditBox* debug;
	sf::RenderWindow* window;
	bool isOK;
	Client* client;

	void loop()
	{
		while (window->isOpen())
		{
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window->close();
				sf::sleep(sf::milliseconds(100));

				panel->draw();

				GuiElement* clicked = panel->isClicked(event);
				if (clicked!=NULL && clicked->getType()==GuiElement::BTN)
				{
					if (clicked->id=="start") {
						client = new Client(strtoint(ePort->getText()), eIPAddress->getText(), eNickname->getText());
						isOK = true;
					}
					/*else if (clicked->id == "send")
					{
						debug->setText("");
					}*/
				}
				panel->type(event);
			}
			if (isOK) break;
		}
	}

	void makeGui()
	{
		//init gui
		panel = new GuiContainer(window);
		lPort = new Label("lport", window, new Coord(10,10), "Port:");
		lIPAddress = new Label("lipaddress", window, new Coord(10,40), "IP:");
		lNickname = new Label("lnickname", window, new Coord(10,70), "Nickname:");
		//lDebug = new Label("ldebug", window, new Coord(10, 160), "incoming:");
		start = new Button("start", window, new Coord(10, 100), "Start client", 100, 25);
		ePort = new EditBox("eport", window, new Coord(80, 10), "54322", 150, 25);
		eIPAddress = new EditBox("eipaddress", window, new Coord(80, 40), "192.168.1.67", 150, 25);
		eNickname = new EditBox("enickname", window, new Coord(80, 70), "client0", 150, 25);
		//debug = new EditBox("debug", window, new Coord(10, 130), "", 150, 25);
		//send = new Button("send", window, new Coord(120, 100), "Send message", 100, 25);
		panel->add(lPort);
		panel->add(lIPAddress);
		panel->add(lNickname);
		panel->add(start);
		panel->add(ePort);
		panel->add(eIPAddress);
		panel->add(eNickname);
		//panel->add(debug);
		//panel->add(send);
		//panel->add(lDebug);
	}

	int strtoint(std::string s)
	{
		std::stringstream ss(s);
		int ret;
		ss >> ret;
		return ret;
	}

};

#endif //STARTGUI_HPP