#include "TankAnimation.h"
#include "../Util/Utils.h"

TankAnimation::TankAnimation(CommonTankInfo *tank, TextureHolder* texture,TextureHolder* bumm, sf::Texture *cannonTexture,sf::Texture *selectTexture, sf::Texture *bulletTexture,sf::Color color)
{
    tankInfo = tank;
    tankState = 0;
    bummState = 0;
    destroyMs = 2;
    for(int i = 0; i<3; i++)
    {
        sprites.push_back(new sf::Sprite());
        sprites[i]->setTexture(*(texture->returnIndex(i)));
        sprites[i]->setColor(color);
        sprites[i]->setPosition(tankInfo->getPosition());
        sprites[i]->setRotation(tankInfo->getTankAngle());
    }
    for(int j = 0; j<4; j++)
    {
        bumms.push_back(new sf::Sprite());
        bumms[j]->setTexture(*(bumm->returnIndex(j)));
        bumms[j]->setColor(color);
        bumms[j]->setOrigin(30.0f,30.0f);
        bumms[j]->setPosition(tankInfo->getPosition());
        bumms[j]->setRotation(tankInfo->getTankAngle());
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
    bullet = new sf::Sprite();
    bullet->setTexture(*bulletTexture);
}
TankAnimation::~TankAnimation(void)
{
    clearPointerContainer(sprites);
    clearPointerContainer(bumms);
    delete cannon;
    delete selection;
    delete bullet;
    tankInfo->setPosition(sf::Vector2f(-100.0f, -100.0f));
}
void TankAnimation::updateTank()
{
    float xScale = tankInfo->getSize().x/sprites[0]->getTexture()->getSize().x;
    float yScale = tankInfo->getSize().y/sprites[0]->getTexture()->getSize().y;
    for(int i = 0; i<3; i++)
    {
        sprites[i]->setPosition(tankInfo->getPosition());
        sprites[i]->setOrigin(18.0f,18.0f);
        sprites[i]->setRotation(tankInfo->getTankAngle());
    }
    for(int j = 0; j<4; j++)
    {
        bumms[j]->setPosition(tankInfo->getPosition());
        bumms[j]->setRotation(tankInfo->getTankAngle());
    }
    cannon->setOrigin(25.0f, 25.0f);
    cannon->setPosition(tankInfo->getPosition());
    cannon->setRotation(tankInfo->getCannonAngle());
    selection->setPosition(tankInfo->getPosition());

    if(tankInfo->getBullet()!=NULL)
        bullet->setPosition(tankInfo->getBullet()->getPosition());
    else
        bullet->setPosition(sf::Vector2f(-100.0f,-100.0f));
}
bool TankAnimation::isSelected()
{
    return tankInfo->isSelected();
}
bool TankAnimation::isDestroyed()
{
    return tankInfo->isDestroyed();
}
sf::Sprite* TankAnimation::getTank()
{
    if(!tankInfo->isInMotion()) return sprites[0];
    if(++tankState==sprites.size()) tankState = 0;
    return sprites[tankState];
}

sf::Sprite* TankAnimation::getBumm()
{
    bummState++;
    if(bummState<destroyMs) return bumms[0];
    if(bummState<destroyMs*2) return bumms[1];
    if(bummState<destroyMs*3) return bumms[2];
    if(bummState<destroyMs*4) return bumms[3];
    return NULL;
}
sf::Sprite* TankAnimation::getSelection()
{
    return selection;
}
sf::Sprite* TankAnimation::getCannon()
{
    return cannon;
}

sf::Sprite* TankAnimation::getBullet()
{
    return bullet;
}