#include "Controller.h"
#include "../Util/Utils.h"
#include <cmath>

Client* Controller::startgui()
{
  StartGui gui;
  return gui.getClient();
}
Controller::Controller(short x, short y, std::string title, unsigned short myId) : myTeamId(myId)
{
  window = new sf::RenderWindow(sf::VideoMode(x,y), title, sf::Style::Close);
  view = new View(window,true);
  addTanks(view);
  addRandomBarrels(view);
}
CommonTankInfo* Controller::getTankOnPosition(float X, float Y)
{
	std::vector<CommonTeamInfo*>::iterator teamIter;
	std::vector<CommonTankInfo*>::iterator tankIter;
	for(teamIter = teams.begin();teamIter!=teams.end();teamIter++)
	{
		for(tankIter = (*teamIter)->getBegin(); tankIter != (*teamIter)->getEnd(); tankIter++)
		{
		float left = (*tankIter)->posX-(*tankIter)->width/2-10.f;
		float right = (*tankIter)->posX+(*tankIter)->width/2+10.f;
		float top = (*tankIter)->posY-(*tankIter)->height/2-10.f;
		float bottom = (*tankIter)->posY+(*tankIter)->height/2+10.f;
		if(left<X && right>X && top<Y && bottom>Y)
			{
				//std::cout<<"\nTank on ("<<(*tankIter)->posX<<","<<(*tankIter)->posY<<") selected\n";
				return *tankIter;
			}
		//std::cout<<"\nTank bounds on ("<<top<<","<<right<<","<<bottom<<","<<left<<")";
		}
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
float Controller::getAngleBetweenPoints(float x, float y, float a, float b)
{
	return std::atan2f(a-x,y-b)*180.0f/3.1412f;
}
void Controller::rotateCannonToPoint(float x, float y)
{
	teams[myTeamId]->getSelected()->cannonOrientation = getAngleBetweenPoints(teams[myTeamId]->getSelected()->posX,teams[myTeamId]->getSelected()->posY,x,y);
	//std::cout<<"Rotated to: "<<teams[myTeamId]->getSelected()->cannonOrientation<<"\n-------------\n";
}
bool Controller::getEvent(sf::Event& ev)
{
	if(events.empty()) return false;
	ev = *events.begin();
	events.pop_front();
  if(ev.type == sf::Event::Closed)
  {
    shutDown();
	return false;
  }
  rotateCannonToPoint((float)sf::Mouse::getPosition(*window).x,(float)sf::Mouse::getPosition(*window).y);

  if(ev.type == sf::Event::MouseButtonPressed)
  {
	  handleSelectedTank(getTankOnPosition((float)sf::Mouse::getPosition(*window).x,(float)sf::Mouse::getPosition(*window).y));
	  return false;
  }
	

	return true;
}
void Controller::handleSelectedTank(CommonTankInfo* tank)
{
	if (tank == NULL) return;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isOwnTeam(tank))//Bal katt, kiválasztás
	selectionHandler(tank);
	//else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && (isOwnTeam(tank) || true)//Jobb katt, másikra esete. True teszt célból
	
}
bool Controller::isOwnTeam(CommonTankInfo* tank)
{
	return tank->team() == myTeamId;
}
void Controller::selectionHandler(CommonTankInfo* tank)
{
	
	std::vector<CommonTankInfo*>::iterator iter = teams[myTeamId]->getBegin();
	for(;iter != teams[myTeamId]->getEnd();iter++)
	{
		(*iter)->selected = false;
	}
	tank->selected = true;
	teams[myTeamId]->setSelected(tank);
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
  {
	  teams.push_back(new CommonTeamInfo(j));
    for(int i = 0; i< 3 ; i++)//players in tank
      {
        CommonTankInfo* t = new CommonTankInfo(j);
        t->height = (float)(40);
        t->width = (float)(30);
        t->cannonOrientation = (float)(std::rand()%359);
        t->orientation = 0.0f;(float)(std::rand()%359);
        t->posX = (float)(std::rand()%630)+30.0f;
        t->posY = (float)(std::rand()%630)+30.0f;
		t->selected = false;
		if(i == 0 && j == myTeamId) t->selected = true;
		t->motionTrigger = false;
		teams[j]->addTank(t);
        v->addTank(t);
      }
  }
}

void Controller::addRandomBarrels(AbstractView* v)
{
  for(int i = 0; i< 10 ; i++)
    {
      //v->addBarrel((float)(std::rand()%700), (float)(std::rand()%700), (float)(std::rand()%10+30), (float)(std::rand()%10+30));
		v->addBarrel((float)(std::rand()%630+30), (float)(std::rand()%630+30), 35.0f, 35.0f);

    }
}
Controller::~Controller(void)
{
	clearPointerContainer(teams);
}
