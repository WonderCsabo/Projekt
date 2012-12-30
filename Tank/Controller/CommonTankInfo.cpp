#include "CommonTankInfo.h"
CommonTankInfo::CommonTankInfo(unsigned short team, unsigned short id,const sf::Vector2f& pos,const sf::Vector2f& s):teamId(team), tankId(id), position(pos), destination(pos), size(s), tankAngle(0.0f), cannonAngle(0.0f), motionTrigger(false), selected(false) {}
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
void CommonTankInfo::startMotion()
{
	motionTrigger = true;
}
void CommonTankInfo::stopMotion()
{
	motionTrigger = false;
}
void CommonTankInfo::reSelect()
{
	selected = true;
}
void CommonTankInfo::deSelect()
{
	selected = false;
}