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
		sprites[i]->setOrigin(tankInfo->getSize().x/2,tankInfo->getSize().x/2);
		sprites[i]->setPosition(tankInfo->getPosition());
		sprites[i]->setRotation(tankInfo->getTankAngle());
	}
	cannon = new sf::Sprite();
	cannon->setTexture(*cannonTexture);
	cannon->setOrigin(25.0f, 25.0f);
	cannon->setOrigin(tankInfo->getSize().x/2,tankInfo->getSize().x/2);
	cannon->setColor(color);
	cannon->setPosition(tankInfo->getPosition());
	cannon->setRotation(tankInfo->getCannonAngle());
	selection = new sf::Sprite();
	selection->setTexture(*selectTexture);
	selection->setOrigin(30.0f, 30.0f);
	selection->setColor(color);
	selection->setPosition(tankInfo->getPosition());
}
TankAnimation::~TankAnimation(void)
{
	clearPointerContainer(sprites);
	delete cannon;
	delete selection;
}
void TankAnimation::updateTank()
{
	float xScale = tankInfo->getSize().x/sprites[0]->getTexture()->getSize().x;
	float yScale = tankInfo->getSize().y/sprites[0]->getTexture()->getSize().y;
	for(int i = 0; i<3; i++)
	{
		sprites[i]->setPosition(tankInfo->getPosition());
		//sprites[i]->setScale(xScale,yScale);
		sprites[i]->setOrigin(18.0f,18.0f);
		//sprites[i]->setOrigin(tankInfo->getSize().x/2,tankInfo->getSize().x/2);
		sprites[i]->setRotation(tankInfo->getTankAngle());
	}
	//cannon->setScale(xScale, yScale);
	cannon->setOrigin(25.0f, 25.0f);
	//cannon->setOrigin(tankInfo->getSize().x/2,tankInfo->getSize().x/2);
	cannon->setPosition(tankInfo->getPosition());
	cannon->setRotation(tankInfo->getCannonAngle());
	selection->setPosition(tankInfo->getPosition());
}
bool TankAnimation::isSelected()
{
	return tankInfo->isSelected();
}
sf::Sprite* TankAnimation::getTank()
{
	if(!tankInfo->isInMotion()) return sprites[0];
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