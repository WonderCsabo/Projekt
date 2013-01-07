#pragma once

#include "AbstractEntity.h"
#include "Tank.h"

class Projectile : public AbstractEntity
{

public:

    Projectile();
    Projectile(const short& posX, const short& posY, const short& sizeX, const short& sizeY, const Tank* const firingTank);

    const Tank* const getFiringTank() const;
    unsigned short getFireDamage() const;

private:

    const Tank* const firingTank;
};