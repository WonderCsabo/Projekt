#include "CommonBulletInfo.h"


CommonBulletInfo::CommonBulletInfo(sf::Vector2f p,sf::Vector2f d):position(p),destination(d){}
CommonBulletInfo::~CommonBulletInfo(void){}


const sf::Vector2f& CommonBulletInfo::getPosition()
{
	return position;
}
const sf::Vector2f& CommonBulletInfo::getDestination()
{
	return destination;
}
void CommonBulletInfo::setPosition(const sf::Vector2f& p)
{
	position = p;
}
void CommonBulletInfo::setDestination(const sf::Vector2f& d)
{
	destination = d;
}