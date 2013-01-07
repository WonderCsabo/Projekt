#include "Projectile.h"

Projectile::Projectile() : firingTank(0) { }

Projectile::Projectile(const short& posX, const short& posY, const short& sizeX, const short& sizeY, const Tank* const firingTank)
    : AbstractEntity(posX, posY, sizeX, sizeY), firingTank(firingTank) { }

const Tank* const Projectile::getFiringTank() const
{
    return firingTank;
}

unsigned short Projectile::getFireDamage() const
{

    return firingTank ? firingTank->getFireDamage() : 0;
}