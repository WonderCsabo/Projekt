#include "CommonTankInfo.h"

CommonTankInfo::CommonTankInfo(unsigned short team, Tank* tank): teamId(team), tankLogic(tank), bullet(0), destroyed(false)
{
	stopShoot();
}

CommonTankInfo::~CommonTankInfo(void) {}

unsigned short CommonTankInfo::getTeamId()
{
	return teamId;
}
unsigned short CommonTankInfo::getTankId()
{
	return tankLogic->getID();
}
sf::Vector2f CommonTankInfo::getPosition()
{
	return sf::Vector2f(tankLogic->getPosX(), tankLogic->getPosY());
}
sf::Vector2f CommonTankInfo::getDestination()
{
	return sf::Vector2f(tankLogic->getDestinationX(), tankLogic->getDestinationY());
}
sf::Vector2f CommonTankInfo::getSize()
{
	return sf::Vector2f(tankLogic->getSizeX(), tankLogic->getSizeY());
}
CommonBulletInfo* CommonTankInfo::getBullet()
{
	return bullet;
}
const float& CommonTankInfo::getTankAngle()
{
	return tankLogic->getTankAngle();
}
const float& CommonTankInfo::getCannonAngle()
{
	return tankLogic->getCannonAngle();
}

Tank* CommonTankInfo::getLogic()
{
	return tankLogic;
}
bool CommonTankInfo::isInMotion()
{
	return tankLogic->isMotion();
}
bool CommonTankInfo::isSelected()
{
	return tankLogic->isSelected();
}
bool CommonTankInfo::isShoot()
{
	return tankLogic->isFiring();
}
bool CommonTankInfo::isDestroyed()
{
	return destroyed;
}
void CommonTankInfo::setPosition(const sf::Vector2f& pos)
{
	tankLogic->setPosX((short) pos.x);
	tankLogic->setPosY((short) pos.y);
}
void CommonTankInfo::setDestination(const sf::Vector2f& dest)
{
	tankLogic->setDestinationX((short) dest.x);
	tankLogic->setDestinationY((short) dest.y);
}
void CommonTankInfo::setTankAngle(const float& angle)
{
	tankLogic->setTankAngle(angle);
}
void CommonTankInfo::setCannonAngle(const float& angle)
{
	tankLogic->setCannonAngle(angle);
}
void CommonTankInfo::setBullet(CommonBulletInfo* foo)
{
	bullet = foo;
}

void CommonTankInfo::updateLogic(Tank* updated)
{
	tankLogic = updated;
	startMotion();
}

void CommonTankInfo::startMotion()
{
	tankLogic->setMotion(true);
}
void CommonTankInfo::stopMotion()
{
	tankLogic->setMotion(false);
	setDestination(getPosition());
}
void CommonTankInfo::startShoot()
{
	tankLogic->setFiring(true);
}
void CommonTankInfo::stopShoot()
{
	tankLogic->setFiring(false);
}
void CommonTankInfo::reSelect()
{
	tankLogic->setSelected(true);
}
void CommonTankInfo::deSelect()
{
	tankLogic->setSelected(false);
}
void CommonTankInfo::destroy()
{
	destroyed = true;
}