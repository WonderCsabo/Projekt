#pragma once
#include <SFML/Graphics.hpp>
#include "CommonBulletInfo.h"
#include "../Logic/Tank.h"
/*This is the adapter of the game logic used in the graphic.*/
class CommonTankInfo
{
private:
	Tank* tankLogic;
	const unsigned short teamId;

	bool motionTrigger;
	bool destroyed;
	CommonBulletInfo* bullet;
	
public:
	/*
	Team id in unsigned short
	*/
	CommonTankInfo(unsigned short, Tank* tank);
	~CommonTankInfo(void);

	unsigned short getTeamId();
	unsigned short getTankId();
	sf::Vector2f getPosition();
	sf::Vector2f getDestination();
	sf::Vector2f getSize();
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
	void updateLogic(Tank* updated);
	
	void startMotion();
	void stopMotion();
	void startShoot();
	void stopShoot();
	void reSelect();
	void deSelect();
	void destroy();
};

