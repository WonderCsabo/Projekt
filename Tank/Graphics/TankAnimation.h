#pragma once

#include <SFML/Graphics.hpp>
#include "../Controller/CommonTankInfo.h"
#include "TextureHolder.h"
#include "../Util/DebugWindow.h"
#include <vector>

class TankAnimation
{
public:
	TankAnimation(CommonTankInfo*,TextureHolder*,TextureHolder*, sf::Texture*,sf::Texture*,sf::Texture*,sf::Color);
	~TankAnimation(void);

	void updateTank();
	bool isSelected();
	bool isDestroyed();
	
	sf::Sprite* getTank();
	sf::Sprite* getBumm();
	sf::Sprite* getSelection();
	sf::Sprite* getCannon();
	sf::Sprite* getBullet();

private:
	unsigned short destroyMs;
	unsigned short tankState;
	unsigned short bummState;
	std::vector<sf::Sprite*> sprites;//Handled
	std::vector<sf::Sprite*> bumms;//Handled
	sf::Sprite* cannon;//Handled
	sf::Sprite* selection;//Handled
	sf::Sprite* bullet;//Handled
	CommonTankInfo* tankInfo;//Should be handled on highest level.
};

