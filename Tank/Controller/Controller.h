#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <list>
#include "CommonTankInfo.h"
#include "CommonTeamInfo.h"
#include "../Graphics/View.h"
#include "../Graphics/AbstractView.h"
#include "../Net/Client.h"
#include "../GUI/StartGui.h"
#include "../Util/DebugWindow.h"
#include "../Util/GetInput.h"
#include "../Util/Os.h"

class Controller
{

private:
	const unsigned short myTeamId;
	std::vector<CommonTeamInfo*> teams;
	sf::RenderWindow *window;
	AbstractView *view;
	std::list<sf::Event> events;
	CommonTankInfo* getTankOnPosition(float, float);
	void handleSelectedTank(CommonTankInfo*);
	void selectionHandler(CommonTankInfo*);
	void rotateCannonToPoint(float, float);
	bool isOwnTeam(CommonTankInfo*);
	float getAngleBetweenPoints(float,float,float,float);
	//DebugWindow d;
public:
	Controller(short x, short y, std::string, unsigned short);
	~Controller(void);
	static Client* startgui();
	void addRandomBarrels(AbstractView* v);
	void addTanks(AbstractView* v);
	sf::RenderWindow* getWindow();
	AbstractView* getView();
	bool programRunning();
	bool getEvent(sf::Event&);
	void recieveEvents();
	void addText(sf::Text);
	void shutDown();
	void refresh();
};

