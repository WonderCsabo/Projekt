#include "Controller.h"
#include "../Util/Utils.h"
#include <cmath>

int Controller::run()
{
	std::srand((unsigned)std::time( 0 ));
	if (client==NULL && !StartGui::isOfflineMode())
		return 1; //return with error
	if (!StartGui::isOfflineMode()) startChat();
	while(programRunning())//runs by the main thread
	{
		sf::Event ev;
		while(getEvent(ev))
		{
			if(client!= NULL)
			{
				client->sendEventMessage(ev);
			}
			if(ev.type == sf::Event::Closed)
			{
				shutdown();
				return 0;
			}
		}
		refresh();
	}
	return 0;
}
void Controller::recieveFromClient()//runs in separate thread
{
	while (programRunning())
	{
		sf::sleep(sf::milliseconds(10));
		MessageObject m = client->getLastMessage();
		if (m.type == MessageObject::CMD && m.message == "shut")
		{
			shutdown();
		}
		else
		{
			if (m.message != "null")
				view->addOutputChat(m.message);
		}
	}
}
void Controller::wrt(const sf::Event &event)
{ 
	if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0))
	{
		writeToConsole = !writeToConsole;
		if (writeToConsole) console = client->getNickname() + ": ";
		view->addInputChat(console);
		return;
	}

	if (writeToConsole && event.type == sf::Event::KeyPressed)
	{
		char c = getChar(event);
		if (c!=0)
			console+=c;
		if (console[0] == '0' && console.length()>1)
			console = console.substr(1, console.length());
		if (event.key.code==sf::Keyboard::Back && console.length()>client->getNickname().length()+2)
			console = console.substr(0, console.length()-1);
		if (event.key.code==sf::Keyboard::Return)
		{
			if (client!=NULL)
			{
				if (console!=client->getNickname()+": ")
				{
					console = console.substr(client->getNickname().length()+2, console.length());
					client->send(console);
				}
			}
			console = "";
			writeToConsole = false;
		}
		view->addInputChat(console);
	}
}
Client* Controller::startGui()
{
	StartGui gui;
	return gui.getClient();
}
void Controller::startChat()
{
	thread = new sf::Thread(&Controller::recieveFromClient,this);
	thread->launch();
}
void Controller::stopChat()
{
	if(thread != NULL)
	{
		thread->terminate();
		delete thread;
	}
}
Controller::Controller(short x, short y, std::string title, unsigned short myId) : myTeamId(myId), 
	map(new Map(x, y))
{
	client = startGui();
	thread = NULL;
	console = "";
	writeToConsole = false;
	window = new sf::RenderWindow(sf::VideoMode(x,y), title, sf::Style::Close);
	view = new View(window);
	tankSpeed = 15.0f;
	rotSpeed = 30.0f;
	bulletSpeed = 30.0f;
	waitMs = 25;
	addTanks(view);
	addRandomBarrels(view);
}
char Controller::getChar(const sf::Event &ev)
{
	if (ev.type == ev.KeyPressed)
	{
		if (ev.key.code>=0 && ev.key.code<=25)
		{
			if (ev.key.shift==false)
				return char(97+ev.key.code);
			else
				return char(65+ev.key.code);
		}
		else if (ev.key.code==sf::Keyboard::Space)
			return ' ';
		else if (ev.key.code>=26 && ev.key.code<=35)
		{
			return char(48+ev.key.code-26);
		}
		else if (ev.key.code>=75 && ev.key.code<=84)
		{
			return char(48+ev.key.code-75);
		}
		else if (ev.key.code == sf::Keyboard::Period)
			return '.';
		else return 0;
	}
	else return 0;
}

CommonTankInfo* Controller::getTankOnPosition(const sf::Vector2f& position, CommonTankInfo* thisTank)
{
	std::vector<CommonTeamInfo*>::iterator teamIter;
	std::vector<CommonTankInfo*>::iterator tankIter;
	for(teamIter = teams.begin(); teamIter!=teams.end(); teamIter++)
	{
		for(tankIter = (*teamIter)->getBegin(); tankIter != (*teamIter)->getEnd(); tankIter++)
		{
			if(thisTank != *tankIter && isTankOnNewPosition(*tankIter, (*tankIter)->getPosition(), position, 10.f))
				return *tankIter;
		}
	}
	return NULL;
}

CommonTankInfo* Controller::isTankOnNewPosition(CommonTankInfo* tank, const sf::Vector2f& newPosition, const sf::Vector2f& position, const float& bounds)
{
	float left = newPosition.x - tank->getSize().x / 2 - bounds;
	float right = newPosition.x + tank->getSize().x / 2 + bounds;
	float top = newPosition.y - tank->getSize().y / 2 - bounds;
	float bottom = newPosition.y + tank->getSize().y / 2 + bounds;

	if(left < position.x && right > position.x && top < position.y && bottom > position.y)
		return tank;
	return 0;
}

bool Controller::programRunning()
{
	if(window == NULL) return false;
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
	rotateCannonToPoint(sf::Vector2f(sf::Mouse::getPosition(*window)));

	if(ev.type == sf::Event::MouseButtonPressed)
	{
		handleMouseClick(getTankOnPosition(sf::Vector2f(sf::Mouse::getPosition(*window))));
		return false;
	}
	else wrt(ev);
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
	if(teams[myTeamId]->getSelected()->isShoot()) return;
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

		sf::Vector2f newPosition;

		if(std::abs(a)<std::abs(i) || std::abs(b)<std::abs(j)) newPosition = tank->getDestination();
		else newPosition = tank->getPosition()+sf::Vector2f(i,j);

		for(auto it = map->getBlocks().cbegin(); it != map->getBlocks().cend(); ++it)
		{
			if(isTankOnNewPosition(tank, newPosition, sf::Vector2f((*it)->getPosX(), (*it)->getPosY()), 17.f))
			{
				tank->stopMotion();
				return;
			}
		}

		if(getTankOnPosition(newPosition, tank))
		{
			tank->stopMotion();
			return;
		}

		tank->setPosition(newPosition);
	}
}

void Controller::moveBullet(CommonTankInfo* tank)
{
	CommonTankInfo* hit = getTankOnPosition(tank->getBullet()->getPosition());
	if(tank->getBullet()->getPosition().x < 0 || tank->getBullet()->getPosition().x > 700 || tank->getBullet()->getPosition().y<0 || tank->getBullet()->getPosition().y > 700)
	{
		tank->stopShoot();
		tank->setBullet(NULL);
	}
	else if(hit == NULL || hit == tank)
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
	clock.restart();
	recieveEvents();
	tankMovements();
	view->drawEverything();

	if(clock.getElapsedTime().asMilliseconds() <= waitMs)
		sf::sleep(sf::milliseconds(waitMs - clock.getElapsedTime().asMilliseconds()));

	//sf::sleep(sf::milliseconds(waitMs));
}
void Controller::shutdown()
{
	stopChat();
	if(client != NULL)	client->shutDown();
	if(window != NULL && window->isOpen())  window->close();
	delete client;
	delete window;
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
			Tank* tank = new Tank(std::rand() % 630 + 30, std::rand() % 630 + 30, 35, 35, i, 0);
			CommonTankInfo* t = new CommonTankInfo(j, tank);
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
		short randX = std::rand()%630+30, randY = std::rand()%630+30;

		v->addBarrel(sf::Vector2f((float)randX, (float)randY), sf::Vector2f(35.0f, 35.0f));
		map->add(new Block(randX, randY, 35, 35));
	}
}

Controller::~Controller(void)
{
	if(map)
		delete map;
	clearPointerContainer(teams);
}
