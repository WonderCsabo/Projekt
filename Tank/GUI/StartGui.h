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

    static bool isOfflineMode();
    static bool isWindowClosed();

private:
    GuiContainer* panel;
    Label* lPort;
    Label* lIPAddress;
    Label* lNickname;
    Button* start;
    Button* offline;
    EditBox* ePort;
    EditBox* eIPAddress;
    EditBox* eNickname;
    sf::RenderWindow* window;
    bool isOK;
    Client* client;

    static bool offlineMode;
    static bool windowclosed;

    void loop();
    void makeGui();
    void tryToConnect();
    int strtoint(std::string s);

};