#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <list>
#include <unordered_map>
#include "CommonTankInfo.h"
#include "CommonTeamInfo.h"
#include "../Graphics/View.h"
#include "../Graphics/AbstractView.h"
#include "../Net/Client.h"
#include "../Logic/Map.h"
#include "../GUI/StartGui.h"
#include "../Util/DebugWindow.h"
#include "../Util/Os.h"
#include "../Sounds/Sounds.h"

class Controller
{
private:
    Client* client;
    Sounds sounds;
    unsigned short myTeamId;
    float tankSpeed;
    float bulletSpeed;
    float rotSpeed;
    int waitMs;
    sf::Clock clock;
    std::vector<CommonTeamInfo*> teams;
    sf::RenderWindow *window;
    AbstractView *view;
    std::list<sf::Event> events;
    bool isGameStarted;

    Map *map;

    std::unordered_map<Tank*, CommonTankInfo*> getCTanks;

    void shutdown();
    CommonTankInfo* getTankOnPosition(const sf::Vector2f&, CommonTankInfo* = 0);
    CommonTankInfo* getOtherTankOnPosition(CommonTankInfo*, const sf::Vector2f&);
    CommonTankInfo* isTankOnNewPosition(CommonTankInfo*, const sf::Vector2f& , const sf::Vector2f& , const float&);
    void addMove(CommonTankInfo*,const sf::Vector2f&);
    void handleMouseClick(CommonTankInfo*);
    void detonate(CommonTankInfo*);
    void handleShoot(const sf::Vector2f&, CommonTankInfo* tank);
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
    void addCurrentPlayerTanks(AbstractView* v, Player* player, const short& playerID);
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
    Controller(short,short,std::string);
    ~Controller(void);
    int run();
    sf::RenderWindow* getWindow();
    AbstractView* getView();


    /*Pass the last sf::Event from the queue.
      Return false, is the querue is empty.*/
    bool getEvent(sf::Event&);

    void refresh();
};

