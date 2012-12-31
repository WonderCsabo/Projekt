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
	view = new View(window);
	tankSpeed = 15.0f;
	rotSpeed = 30.0f;
	bulletSpeed = 30.0f;
	waitMs = 25;
	addTanks(view);
	addRandomBarrels(view);
}
CommonTankInfo* Controller::getTankOnPosition(const sf::Vector2f& position)
{
	std::vector<CommonTeamInfo*>::iterator teamIter;
	std::vector<CommonTankInfo*>::iterator tankIter;
	for(teamIter = teams.begin(); teamIter!=teams.end(); teamIter++)
	{
		for(tankIter = (*teamIter)->getBegin(); tankIter != (*teamIter)->getEnd(); tankIter++)
		{
			float left = (*tankIter)->getPosition().x-(*tankIter)->getSize().x/2-10.f;
			float right = (*tankIter)->getPosition().x+(*tankIter)->getSize().x/2+10.f;
			float top = (*tankIter)->getPosition().y-(*tankIter)->getSize().y/2-10.f;
			float bottom = (*tankIter)->getPosition().y+(*tankIter)->getSize().y/2+10.f;
			if(left<position.x && right>position.x && top<position.y && bottom>position.y)
			{
				return *tankIter;
			}
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
float Controller::getAngleBetweenPoints(const sf::Vector2f& A, const sf::Vector2f& B)
{
	return std::atan2f(B.x-A.x,A.y-B.y)*180.0f/3.1412f;
}
void Controller::rotateCannonToPoint(const sf::Vector2f& A)
{
	teams[myTeamId]->getSelected()->setCannonAngle(getAngleBetweenPoints(teams[myTeamId]->getSelected()->getPosition(),A));
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
	rotateCannonToPoint(sf::Vector2f(sf::Mouse::getPosition(*window)));

	if(ev.type == sf::Event::MouseButtonPressed)
	{
		handleMouseClick(getTankOnPosition(sf::Vector2f(sf::Mouse::getPosition(*window))));
		return false;
	}
	return true;
}
void Controller::handleMouseClick(CommonTankInfo* tank)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if(tank == NULL)
			addMove(teams[myTeamId]->getSelected(), sf::Vector2f(sf::Mouse::getPosition(*window)));
		else
			handleShoot(sf::Vector2f(sf::Mouse::getPosition(*window)));
	}
	else
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			selectionHandler(tank);
		}
	}
}
void Controller::handleShoot(const sf::Vector2f& A)
{
	float a = std::floorf(A.x)-std::floorf(teams[myTeamId]->getSelected()->getPosition().x);
	float b = std::floorf(A.y)-std::floorf(teams[myTeamId]->getSelected()->getPosition().y);
	float c = std::sqrtf(a*a+b*b);
	float i = a/c*bulletSpeed;
	float j = b/c*bulletSpeed;
	teams[myTeamId]->getSelected()->setBullet(new CommonBulletInfo(teams[myTeamId]->getSelected()->getPosition(),sf::Vector2f(i,j)));
	teams[myTeamId]->getSelected()->startShoot();
}
void Controller::addMove(CommonTankInfo* tank,const sf::Vector2f& destination)
{
	tank->setDestination(destination);
	tank->startMotion();
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
			if(tank->isShoot() && tank->getBullet() != NULL) moveBullet(tank);
			if(tank->isInMotion()) applyMove(tank);
		}
	}
}
void Controller::applyMove(CommonTankInfo* tank)
{
	if(tank->getPosition() == tank->getDestination())
	{
		tank->stopMotion();
		return;
	}
	float desired = getAngleBetweenPoints(tank->getPosition(), tank->getDestination());
	if(std::floor(desired) != std::floor(tank->getTankAngle()))
	{
		float actual = tank->getTankAngle();
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
			tank->setTankAngle(desired);
			return;
		}
		if(actual < 0) actual = 360 + actual;
		if(actual > 360) actual = actual-360;
		if(actual>180) actual -= 360;

		tank->setTankAngle(actual);
	}
	else if(std::floorf(tank->getDestination().x)!=std::floorf(tank->getPosition().x) && std::floorf(tank->getDestination().y)!= std::floorf(tank->getPosition().y))
	{
		float a = std::floorf(tank->getDestination().x)-std::floorf(tank->getPosition().x);
		float b = std::floorf(tank->getDestination().y)-std::floorf(tank->getPosition().y);
		float c = std::sqrtf(a*a+b*b);
		float i = a/c*tankSpeed;
		float j = b/c*tankSpeed;
		if(std::abs(a)<std::abs(i) || std::abs(b)<std::abs(j)) tank->setPosition(tank->getDestination());
		else tank->setPosition(tank->getPosition()+sf::Vector2f(i,j));
	}
}
void Controller::moveBullet(CommonTankInfo* tank)
{
	CommonTankInfo* hit = getTankOnPosition(tank->getBullet()->getPosition());
	if(hit == NULL || hit == tank)
	{
		tank->getBullet()->setPosition(tank->getBullet()->getPosition()+tank->getBullet()->getDestination());
	}
	else
	{
		tank->stopShoot();
		tank->setBullet(NULL);
		hit->destroy();
		//hit->setPosition(sf::Vector2f(-100.0f,-100.0f));
	}
}
bool Controller::isOwnTeam(CommonTankInfo* tank)
{
	return tank->getTeamId() == myTeamId;
}
void Controller::selectionHandler(CommonTankInfo* tank)
{
	CommonTankInfo* temp = teams[myTeamId]->getSelected();
	bool reselect = false;
	if(tank == NULL) return;
	std::vector<CommonTankInfo*>::iterator iter = teams[myTeamId]->getBegin();
	for(; iter != teams[myTeamId]->getEnd(); iter++)
	{
		(*iter)->deSelect();
		if((*iter) == tank)
		{
			reselect = true;
			tank->reSelect();
			teams[myTeamId]->setSelected(tank);
		}
	}
	if(!reselect)
	{
		temp->reSelect();
		teams[myTeamId]->setSelected(temp);
	}
}
void Controller::refresh()
{
	recieveEvents();
	tankMovements();
	view->drawEverything();
	sf::sleep(sf::milliseconds(waitMs));
}
void Controller::shutDown()
{
	window->close();
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
	for(unsigned short j = 0; j < 3; j++)//teams
	{
		teams.push_back(new CommonTeamInfo(j));
		for(unsigned short i = 0; i< 7 ; i++)//players in tank
		{
			CommonTankInfo* t = new CommonTankInfo(j,i,sf::Vector2f((float)(std::rand()%630)+30.0f,(float)(std::rand()%630)+30.0f), sf::Vector2f(35.0f, 35.0f));
			if(i == 0 && j == myTeamId) t->reSelect();
			teams[j]->addTank(t);
			v->addTank(t);
		}
	}
}

void Controller::addRandomBarrels(AbstractView* v)
{
	for(int i = 0; i< 10 ; i++)
	{
		v->addBarrel(sf::Vector2f((float)(std::rand()%630+30), (float)(std::rand()%630+30)), sf::Vector2f(35.0f, 35.0f));

	}
}

Controller::~Controller(void)
{
	clearPointerContainer(teams);
}
