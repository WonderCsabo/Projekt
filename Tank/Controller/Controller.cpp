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
	tankSpeed = 20.0f;
	rotSpeed = 10.0f;
	addTanks(view);
	addRandomBarrels(view);
}
CommonTankInfo* Controller::getTankOnPosition(float X, float Y)
{
	std::vector<CommonTeamInfo*>::iterator teamIter;
	std::vector<CommonTankInfo*>::iterator tankIter;
	for(teamIter = teams.begin(); teamIter!=teams.end(); teamIter++)
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
		handleMouseClick(getTankOnPosition((float)sf::Mouse::getPosition(*window).x,(float)sf::Mouse::getPosition(*window).y));
		return false;
	}
	return true;
}
void Controller::handleMouseClick(CommonTankInfo* tank)
{
	if (tank == NULL && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		addMove(teams[myTeamId]->getSelected(), (float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y);
	}
	else
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))//Bal katt, kiválasztás
		{
			selectionHandler(tank);
		}
	}
	//else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && (isOwnTeam(tank) || true)//Jobb katt, másikra esete. True teszt célból
}
void Controller::addMove(CommonTankInfo* tank, float x, float y)
{
	//std::cout<<"("<<x<<","<<y<<")\n";
	tank->desX = x;
	tank->desY = y;
	tank->motionTrigger = true;
}
void Controller::tankMovements()
{
	std::vector<CommonTeamInfo*>::iterator teamIter;
	std::vector<CommonTankInfo*>::iterator tankIter;
	CommonTankInfo* tank;
	for(teamIter = teams.begin(); teamIter!=teams.end(); teamIter++)
	{
		for(tankIter = (*teamIter)->getBegin(); tankIter != (*teamIter)->getEnd(); tankIter++)
		{
			tank = (*tankIter);
			if(tank->motionTrigger) applyMove(tank);
		}
	}
}
void Controller::applyMove(CommonTankInfo* tank)
{
	if(tank->posX == tank->desX && tank->posY == tank->desY)
	{
		tank->motionTrigger = false;
		return;
	}
	float desired = getAngleBetweenPoints(tank->posX, tank->posY, tank->desX, tank->desY);
	if(std::floor(desired) != std::floor(tank->orientation))
	{
		float actual = tank->orientation;
		if(desired<0) desired+=360;
		if(actual<0) actual += 360;
		if(desired>actual)
		{
			if(desired<180.0f+actual) actual += rotSpeed;
			else actual -= rotSpeed;
		}
		else
		{
			if(actual<180.0f+desired) actual -= rotSpeed;
			else actual += rotSpeed;
		}



		float difference = std::abs(actual-desired);
		if(difference > 180.0f) difference = 360-difference;
		//std::cout<<"|actual-desire|: "<<actual<<"-"<<desired<<"="<<difference<<"\n";
		if(difference<rotSpeed)
		{

			if(desired<0) desired = 360 +desired;
			if(desired > 360) desired = desired-360;
			if(desired>180) desired -= 360;
			tank->orientation = desired;
			return;
		}
		if(actual < 0) actual = 360 + actual;
		if(actual > 360) actual = actual-360;
		if(actual>180) actual -= 360;

		tank->orientation = actual;
	}
	else if(std::floorf(tank->desX)!=std::floorf(tank->posX) && std::floorf(tank->desY)!= std::floorf(tank->posY))
	{
		float a = std::floorf(tank->desX)-std::floorf(tank->posX);
		float b = std::floorf(tank->desY)-std::floorf(tank->posY);
		float c = std::sqrtf(a*a+b*b);
		float i = a/c*tankSpeed;
		float j = b/c*tankSpeed;
		if(std::abs(a)<std::abs(i)) tank->posX = tank->desX;
		else tank->posX += i;
		if(std::abs(b)<std::abs(j)) tank->posY = tank->desY;
		else tank->posY += j;
	}
}
bool Controller::isOwnTeam(CommonTankInfo* tank)
{
	return tank->team() == myTeamId;
}
void Controller::selectionHandler(CommonTankInfo* tank)
{
	CommonTankInfo* temp = teams[myTeamId]->getSelected();
	bool reselect = false;
	if(tank == NULL) return;
	std::vector<CommonTankInfo*>::iterator iter = teams[myTeamId]->getBegin();
	for(; iter != teams[myTeamId]->getEnd(); iter++)
	{
		(*iter)->selected = false;
		if((*iter) == tank)
		{
			reselect = true;
			tank->selected = true;
			teams[myTeamId]->setSelected(tank);
		}
	}
	if(!reselect)
	{
		temp->selected = true;
		teams[myTeamId]->setSelected(temp);
	}
}
void Controller::refresh()
{
	tankMovements();
	view->drawEverything();
	sf::sleep(sf::milliseconds(10));
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
			t->orientation = 0.0f;
			(float)(std::rand()%359);
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
