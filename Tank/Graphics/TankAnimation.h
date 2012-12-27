#pragma once

#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "TextureHolder.h"
#include "../Util/DebugWindow.h"
#include <vector>
class TankAnimation
{
private:
	unsigned short state;
	std::vector<sf::Sprite*> sprites;
	Tank* tankInfo;
public:
	TankAnimation(Tank*,TextureHolder*, sf::Color);
	bool isIt(Tank*);
	void setTank(Tank*);
	sf::Sprite* getSprite();
	~TankAnimation(void);
};

