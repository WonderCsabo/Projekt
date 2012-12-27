#pragma once

#include <SFML/Graphics.hpp>
#include "../Net/Client.h"
#include "GuiContainer.h"

class StartGui
{
public:
	StartGui();
	~StartGui();

	Client* getClient();

private:
	GuiContainer* panel;
	Label* lPort;
	Label* lIPAddress;
	Label* lNickname;
	Button* start;
	EditBox* ePort;
	EditBox* eIPAddress;
	EditBox* eNickname;
	sf::RenderWindow* window;
	bool isOK;
	Client* client;

	void loop();
	void makeGui();
	int strtoint(std::string s);

};