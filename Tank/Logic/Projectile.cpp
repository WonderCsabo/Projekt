#include "Projectile.h"

Projectile::Projectile() : firingTank(0) { }

Projectile::Projectile(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY, const Tank* const firingTank)
    : AbstractEntity(posX, posY, sizeX, sizeY), firingTank(firingTank) { }

const Tank* const Projectile::getFiringTank() const
{
    return firingTank;
}

unsigned short Projectile::getFireDamage() const
{

    return firingTank ? firingTank->getFireDamage() : 0;
}