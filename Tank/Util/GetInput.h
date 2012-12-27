#pragma once

#include "../Graphics/AbstractView.h"
#include "../Net/Client.h"
#include "../Net/MessageObject.h"

void recieveFromClient(AbstractView* view, Client* client, bool& run);

char getChar(sf::Event& ev);

std::string wrt(Client* client, sf::RenderWindow* window, sf::Text& consoleText, std::string& console, sf::Event& event, bool& writeToConsole);