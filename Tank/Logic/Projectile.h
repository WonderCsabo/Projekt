#pragma once

#include "AbstractEntity.h"
#include "Tank.h"

class Projectile : public AbstractEntity
{

public:

    Projectile();
    Projectile(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY, const Tank* const firingTank);

    const Tank* const getFiringTank() const;
    unsigned short getFireDamage() const;

private:

    const Tank* const firingTank;
};