#include "TankAnimation.h"
#include "../Util/Utils.h"

TankAnimation::TankAnimation(CommonTankInfo *tank, TextureHolder* texture, sf::Texture *cannonTexture, sf::Color color)
{
  tankInfo = tank;
  state = 0;
  for(int i = 0; i<3; i++)
    {
      sprites.push_back(new sf::Sprite());
      sprites[i]->setTexture(*(texture->returnIndex(i)));
      sprites[i]->setColor(color);
	  sprites[i]->setOrigin(15.0f, 20.0f);
      sprites[i]->setPosition(tankInfo->posX,tankInfo->posY);
      sprites[i]->setRotation(tankInfo->orientation);
      sprites[i]->setScale(tankInfo->width/sprites[i]->getTexture()->getSize().x,tankInfo->height/sprites[i]->getTexture()->getSize().y);
    }
  cannon = new sf::Sprite();
  cannon->setTexture(*cannonTexture);
  cannon->setOrigin(25.0f, 25.0f);
  cannon->setColor(color);
  cannon->setPosition(tankInfo->posX+15.0f,tankInfo->posY+20.0f);
  cannon->setRotation(tankInfo->cannonOrientation);
}
sf::Sprite* TankAnimation::getTank()
{
  if(++state==sprites.size()) state = 0;
  return sprites[state];
}
sf::Sprite* TankAnimation::getCannon()
{
  return cannon;
}
bool TankAnimation::isIt(CommonTankInfo* t)
{
  return t==tankInfo;
}
void TankAnimation::setTank(CommonTankInfo* t)
{
  tankInfo = t;
  for(int i = 0; i<3; i++)
    {
      sprites[i]->setPosition(tankInfo->posX,tankInfo->posY);
      sprites[i]->setRotation(tankInfo->orientation);
      sprites[i]->setScale(tankInfo->width/sprites[i]->getTexture()->getSize().x,tankInfo->height/sprites[i]->getTexture()->getSize().y);
    }
}
TankAnimation::~TankAnimation(void)
{
  clearPointerContainer(sprites);
}
