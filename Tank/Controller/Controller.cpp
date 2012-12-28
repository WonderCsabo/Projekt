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
CommonTankInfo* Controller::getTankOnPosition(float X, float Y)
{
	//std::cout<<"\nCliccked on: ("<<X<<","<<Y<<");";
	std::vector<CommonTankInfo*>::iterator iter;
	for(iter = tanks.begin();iter!=tanks.end();iter++)
	{
		float left = (*iter)->posX-(*iter)->width/2-10.f;
		float right = (*iter)->posX+(*iter)->width/2+10.f;
		float top = (*iter)->posY-(*iter)->height/2-10.f;
		float bottom = (*iter)->posY+(*iter)->height/2+10.f;
		if(left<X && right>X && top<Y && bottom>Y)
			{
		//		std::cout<<"\nTank on ("<<(*iter)->posX<<","<<(*iter)->posY<<") selected\n";
				return *iter;
			}
	//	std::cout<<"\nTank bounds on ("<<top<<","<<right<<","<<bottom<<","<<left<<")";
	}
	return NULL;
}
bool Controller::programRunning()
{
  return window->isOpen();
}
sf::RenderWindow* Controller::getWindow()
{
  return window;
}
bool Controller::getEvent(sf::Event& ev)
{
	if(events.empty()) return false;
	ev = *events.begin();
	events.pop_front();
  if(ev.type == sf::Event::Closed)
    shutDown();
  if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	  handleSelectedTank(getTankOnPosition(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y));
	
	return true;
}
void Controller::handleSelectedTank(CommonTankInfo* tank)
{
	if (tank == NULL) return;
	if(tank->selected) tank->selected= false;
	else tank->selected = true;
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
void Controller::recieveEvents()
{
  sf::Event ev;
  while(window->pollEvent(ev)) 
  {
  events.push_back(ev);
  }
}


AbstractView* Controller::getView()
{
  return view;
}

void Controller::addTanks(AbstractView* v)
{
  for(int j = 0; j < 2; j++)//teams
    for(int i = 0; i< 3 ; i++)//players in tank
      {
        CommonTankInfo* t = new CommonTankInfo(j);
        t->height = (float)(40);
        t->width = (float)(30);
        t->cannonOrientation = (float)(std::rand()%359);
        t->orientation = 0.0f;//(float)(std::rand()%359);
        t->posX = (float)(std::rand()%700);
        t->posY = (float)(std::rand()%700);
		t->selected = false;
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
