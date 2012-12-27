#pragma once

#include <SFML/Graphics.hpp>
#include "CommonTankInfo.h"
#include "TextureHolder.h"
#include "../Util/DebugWindow.h"
#include <vector>
class TankAnimation
{
private:
	unsigned short state;
	std::vector<sf::Sprite*> sprites;
	CommonTankInfo* tankInfo;
public:
	TankAnimation(CommonTankInfo*,TextureHolder*, sf::Color);
	bool isIt(CommonTankInfo*);
	void setTank(CommonTankInfo*);
	sf::Sprite* getSprite();
	~TankAnimation(void);
};

