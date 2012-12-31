#pragma once
#include <SFML/Graphics.hpp>
#include "CommonBulletInfo.h"
/*This is the adapter of the game logic used in the graphic.*/
class CommonTankInfo
{
private:
	const unsigned short teamId;
	const unsigned short tankId;

	sf::Vector2f position;
	sf::Vector2f destination;
	sf::Vector2f size;
	float tankAngle;
	float cannonAngle;
	bool motionTrigger;
	bool shootTrigger;
	bool destroyed;
	bool selected;
	CommonBulletInfo* bullet;


public:
	/*
	Team id in unsigned short
	Tank id in unsigned short
	Tank position in sf::Vector2f
	Tank size in sf::Vector2f
	*/
	CommonTankInfo(unsigned short, unsigned short,const sf::Vector2f&,const sf::Vector2f&);
	~CommonTankInfo(void);

	unsigned short getTeamId();
	unsigned short getTankId();
	const sf::Vector2f& getPosition();
	const sf::Vector2f& getDestination();
	const sf::Vector2f& getSize();
	CommonBulletInfo* getBullet();
	const float& getTankAngle();
	const float& getCannonAngle();
	bool isInMotion();
	bool isSelected();
	bool isShoot();
	bool isDestroyed();
	void setPosition(const sf::Vector2f&);
	void setDestination(const sf::Vector2f&);
	void setTankAngle(const float&);
	void setCannonAngle(const float&);
	void setBullet(CommonBulletInfo*);
	
	void startMotion();
	void stopMotion();
	void startShoot();
	void stopShoot();
	void reSelect();
	void deSelect();
	void destroy();
};

