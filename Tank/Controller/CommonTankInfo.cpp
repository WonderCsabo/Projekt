#include "CommonTankInfo.h"
CommonTankInfo::CommonTankInfo(unsigned short team, unsigned short id,const sf::Vector2f& pos,const sf::Vector2f& s):teamId(team), tankId(id), position(pos), destination(pos), size(s), tankAngle(0.0f), cannonAngle(0.0f), motionTrigger(false), selected(false)
{
bullet = false;
destroyed = false;
stopShoot();
}
CommonTankInfo::~CommonTankInfo(void) {}

unsigned short CommonTankInfo::getTeamId()
{
	return teamId;
}
unsigned short CommonTankInfo::getTankId()
{
	return tankId;
}
const sf::Vector2f& CommonTankInfo::getPosition()
{
	return position;
}
const sf::Vector2f& CommonTankInfo::getDestination()
{
	return destination;
}
const sf::Vector2f& CommonTankInfo::getSize()
{
	return size;
}
CommonBulletInfo* CommonTankInfo::getBullet()
{
	return bullet;
}
const float& CommonTankInfo::getTankAngle()
{
	return tankAngle;
}
const float& CommonTankInfo::getCannonAngle()
{
	return cannonAngle;
}
bool CommonTankInfo::isInMotion()
{
	return motionTrigger;
}
bool CommonTankInfo::isSelected()
{
	return selected;
}
bool CommonTankInfo::isShoot()
{
	return shootTrigger;
}
bool CommonTankInfo::isDestroyed()
{
	return destroyed;
}
void CommonTankInfo::setPosition(const sf::Vector2f& foo)
{
	position = foo;
}
void CommonTankInfo::setDestination(const sf::Vector2f& foo)
{
	destination = foo;
}
void CommonTankInfo::setTankAngle(const float& foo)
{
	tankAngle = foo;
}
void CommonTankInfo::setCannonAngle(const float& foo)
{
	cannonAngle = foo;
}
void CommonTankInfo::setBullet(CommonBulletInfo* foo)
{
	bullet = foo;
}
void CommonTankInfo::startMotion()
{
	motionTrigger = true;
}
void CommonTankInfo::stopMotion()
{
	motionTrigger = false;
}
void CommonTankInfo::startShoot()
{
	shootTrigger = true;
}
void CommonTankInfo::stopShoot()
{
	shootTrigger = false;
}
void CommonTankInfo::reSelect()
{
	selected = true;
}
void CommonTankInfo::deSelect()
{
	selected = false;
}
void CommonTankInfo::destroy()
{
	destroyed = true;
}