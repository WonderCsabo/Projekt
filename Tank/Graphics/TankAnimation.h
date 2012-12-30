#pragma once

#include <SFML/Graphics.hpp>
#include "../Controller/CommonTankInfo.h"
#include "TextureHolder.h"
#include "../Util/DebugWindow.h"
#include <vector>

class TankAnimation
{
public:
	TankAnimation(CommonTankInfo*,TextureHolder*, sf::Texture*,sf::Texture*,sf::Color);
	~TankAnimation(void);


	void updateTank();
	bool isSelected();

	sf::Sprite* getTank();
	sf::Sprite* getSelection();
	sf::Sprite* getCannon();

private:
	unsigned short state;
	std::vector<sf::Sprite*> sprites;//Handled
	sf::Sprite* cannon;//Handled
	sf::Sprite* selection;//Handled
	CommonTankInfo* tankInfo;//Should be handled on highest level.
};

