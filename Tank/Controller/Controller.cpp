#include "Controller.h"
#include "../Util/Utils.h"

Client* Controller::startgui()
{
  StartGui gui;
  return gui.getClient();
}
Controller::Controller(short x, short y, std::string title)
{
  window = new sf::RenderWindow(sf::VideoMode(x,y), title, sf::Style::Close);
  view = new View(window,true);
  addTanks(view);
  addRandomBarrels(view);
}
bool Controller::programRunning()
{
  return window->isOpen();
}
sf::RenderWindow* Controller::getWindow()
{
  return window;
}
sf::Event Controller::getEvent()
{
  return event;
}
void Controller::refresh()
{
  view->drawEverything();
  sf::sleep(sf::milliseconds(70));
}
void Controller::shutDown()
{
  window->close();
}
void Controller::addText(sf::Text text)
{
  view->addText(text);
}
bool Controller::pollEvent()
{
  if(window->pollEvent(event) == false) return false;
  if(event.type == sf::Event::Closed)
    shutDown();
  return true;
}

AbstractView* Controller::getView()
{
  return view;
}

void Controller::addTanks(AbstractView* v)
{
  for(int j = 0; j < 2; j++)
    for(int i = 0; i< 3 ; i++)
      {
        CommonTankInfo* t = new CommonTankInfo();
        t->height = (float)(40);
        t->width = (float)(30);
        t->cannonOrientation = (float)(std::rand()%359);
        t->orientation = 0.0f;//(float)(std::rand()%359);
        t->posX = (float)(std::rand()%700);
        t->posY = (float)(std::rand()%700);
        t->team = j;
        tanks.push_back(t);
        v->addTank(t);
      }
}

void Controller::addRandomBarrels(AbstractView* v)
{
  for(int i = 0; i< 50 ; i++)
    {
      v->addBarrel((float)(std::rand()%700), (float)(std::rand()%700), (float)(std::rand()%10+30), (float)(std::rand()%10+30));
    }
}
Controller::~Controller(void)
{
  clearPointerContainer(tanks);
}
