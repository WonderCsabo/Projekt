#include "TankAnimation.h"

TankAnimation::TankAnimation(Tank *tank, TextureHolder* texture, sf::Color color)
{
	tankInfo = tank;
	state = 0;
	for(int i = 0; i<3;i++)
	{
	sprites.push_back(new sf::Sprite());
	sprites[i]->setTexture(*(texture->returnIndex(i)));
	sprites[i]->setColor(color);
	sprites[i]->setPosition(tankInfo->posX,tankInfo->posY);
	sprites[i]->setRotation(tankInfo->orientation);
	sprites[i]->setScale(tankInfo->width/sprites[i]->getTexture()->getSize().x,tankInfo->height/sprites[i]->getTexture()->getSize().y);
	}
}

sf::Sprite* TankAnimation::getSprite()
{
	if(++state==sprites.size()) state = 0;
	return sprites[state];
}
bool TankAnimation::isIt(Tank* t)
{
	return t==tankInfo;
}
void TankAnimation::setTank(Tank* t)
{
	tankInfo = t;
	for(int i = 0; i<3;i++)
	{
	sprites[i]->setPosition(tankInfo->posX,tankInfo->posY);
	sprites[i]->setRotation(tankInfo->orientation);
	sprites[i]->setScale(tankInfo->width/sprites[i]->getTexture()->getSize().x,tankInfo->height/sprites[i]->getTexture()->getSize().y);
	}
}
TankAnimation::~TankAnimation(void)
{
	for(unsigned i = 0; i< sprites.size(); i++)
	{
		delete sprites[i];
	}
}
