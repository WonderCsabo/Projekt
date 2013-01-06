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
#include "../Util/Os.h"

class Controller
{
private:
	Client* client;
	const unsigned short myTeamId;
	float tankSpeed;
	float bulletSpeed;
	float rotSpeed;
	int waitMs;
	std::vector<CommonTeamInfo*> teams;
	sf::RenderWindow *window;
	AbstractView *view;
	std::list<sf::Event> events;
	void shutdown();
	CommonTankInfo* getTankOnPosition(const sf::Vector2f&);
	void addMove(CommonTankInfo*,const sf::Vector2f&);
	void handleMouseClick(CommonTankInfo*);
	void detonate(CommonTankInfo*);
	void handleShoot(const sf::Vector2f&);
	void selectionHandler(CommonTankInfo*);
	void rotateCannonToPoint(const sf::Vector2f&);
	void tankMovements();
	void applyMove(CommonTankInfo*);
	void moveBullet(CommonTankInfo*);
	void detonateAnimation(CommonTankInfo*);
	bool isOwnTeam(CommonTankInfo*);
	float getAngleBetweenPoints(const sf::Vector2f&,const sf::Vector2f&);
	void addRandomBarrels(AbstractView* v);
	void addTanks(AbstractView* v);
	void recieveEvents();
	static Client* startGui();
	sf::Thread* thread;
	void startChat();
	void stopChat();
	std::string console;
	char getChar(const sf::Event &);
	bool writeToConsole;
	void wrt(const sf::Event &);
	void recieveFromClient();
	bool programRunning();
public:
	/*
	The Game window size x,y in short.
	The Window title.
	The own team id.
	*/
	Controller(short,short,std::string,unsigned short);
	~Controller(void);
	int run();
	sf::RenderWindow* getWindow();
	AbstractView* getView();


	/*Pass the last sf::Event from the queue.
	  Return false, is the querue is empty.*/
	bool getEvent(sf::Event&);

	void refresh();
};

