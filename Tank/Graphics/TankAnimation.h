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
  sf::Sprite* cannon;
  CommonTankInfo* tankInfo;
public:
	TankAnimation(CommonTankInfo*,TextureHolder*, sf::Texture*,sf::Color);
  bool isIt(CommonTankInfo*);
  void setTank(CommonTankInfo*);
  sf::Sprite* getTank();
  sf::Sprite* getCannon();
  ~TankAnimation(void);
};

