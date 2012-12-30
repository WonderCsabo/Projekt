#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <list>
#include <map>
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
	float tankSpeed;
	float rotSpeed;
	std::vector<CommonTeamInfo*> teams;
	sf::RenderWindow *window;
	AbstractView *view;
	std::list<sf::Event> events;
	CommonTankInfo* getTankOnPosition(const sf::Vector2f&);
	void addMove(CommonTankInfo*,const sf::Vector2f&);
	void handleMouseClick(CommonTankInfo*);
	void selectionHandler(CommonTankInfo*);
	void rotateCannonToPoint(const sf::Vector2f&);
	void tankMovements();
	void applyMove(CommonTankInfo*);
	bool isOwnTeam(CommonTankInfo*);
	float getAngleBetweenPoints(const sf::Vector2f&,const sf::Vector2f&);
	void addRandomBarrels(AbstractView* v);
	void addTanks(AbstractView* v);
	void recieveEvents();
public:
	/*
	The Game window size x,y in short.
	The Window title.
	The own team id.
	*/
	Controller(short,short,std::string,unsigned short);
	~Controller(void);

	static Client* startgui();

	sf::RenderWindow* getWindow();
	AbstractView* getView();

	/*Is the Window still open?*/
	bool programRunning();

	/*Pass the last sf::Event from the queue.
	  Return false, is the querue is empty.*/
	bool getEvent(sf::Event&);


	void shutDown();
	void refresh();
};

