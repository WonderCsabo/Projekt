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
  sf::Sprite* selection;
  CommonTankInfo* tankInfo;
public:
	TankAnimation(CommonTankInfo*,TextureHolder*, sf::Texture*,sf::Texture*,sf::Color);
  bool isIt(CommonTankInfo*);
  bool isSelected();
  void setTank(CommonTankInfo*);
  sf::Sprite* getTank();
  sf::Sprite* getSelection();
  sf::Sprite* getCannon();
  ~TankAnimation(void);
};

