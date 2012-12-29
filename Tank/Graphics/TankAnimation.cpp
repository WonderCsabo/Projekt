#include "TankAnimation.h"
#include "../Util/Utils.h"

TankAnimation::TankAnimation(CommonTankInfo *tank, TextureHolder* texture, sf::Texture *cannonTexture,sf::Texture *selectTexture, sf::Color color)
{
  tankInfo = tank;
  state = 0;
  for(int i = 0; i<3; i++)
    {
      sprites.push_back(new sf::Sprite());
      sprites[i]->setTexture(*(texture->returnIndex(i)));
      sprites[i]->setColor(color);
	  sprites[i]->setOrigin(18.0f,18.0f);
      sprites[i]->setPosition(tankInfo->posX,tankInfo->posY);
      sprites[i]->setRotation(tankInfo->orientation);
      //sprites[i]->setScale(tankInfo->width/sprites[i]->getTexture()->getSize().x,tankInfo->height/sprites[i]->getTexture()->getSize().y);
    }
  cannon = new sf::Sprite();
  cannon->setTexture(*cannonTexture);
  cannon->setOrigin(25.0f, 25.0f);
  cannon->setColor(color);
  cannon->setPosition(tankInfo->posX,tankInfo->posY);
  cannon->setRotation(tankInfo->cannonOrientation);
  selection = new sf::Sprite();
  selection->setTexture(*selectTexture);
  selection->setOrigin(30.0f, 30.0f);
  selection->setColor(color);
  selection->setPosition(tankInfo->posX,tankInfo->posY);
}
sf::Sprite* TankAnimation::getTank()
{
  if(++state==sprites.size()) state = 0;
  return sprites[state];
}
sf::Sprite* TankAnimation::getSelection()
{
  return selection;
}
sf::Sprite* TankAnimation::getCannon()
{
  return cannon;
}
//bool TankAnimation::isIt(CommonTankInfo* t)
//{
//  return t==tankInfo;
//}
bool TankAnimation::isSelected()
{
  return tankInfo->selected;
}
void TankAnimation::updateTank()
{
  for(int i = 0; i<3; i++)
    {
      sprites[i]->setPosition(tankInfo->posX,tankInfo->posY);
      sprites[i]->setRotation(tankInfo->orientation);
      sprites[i]->setScale(tankInfo->width/sprites[i]->getTexture()->getSize().x,tankInfo->height/sprites[i]->getTexture()->getSize().y);
    }
  cannon->setPosition(tankInfo->posX,tankInfo->posY);
  cannon->setRotation(tankInfo->cannonOrientation);
  //std::cout<<"Cannon rotated to :"<<tankInfo->cannonOrientation<<"\n";
  selection->setPosition(tankInfo->posX,tankInfo->posY);
}
TankAnimation::~TankAnimation(void)
{
  clearPointerContainer(sprites);
}
