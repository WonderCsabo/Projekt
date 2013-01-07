#pragma once

#include <iostream>
#include "AbstractEntity.h"

class Block : public AbstractEntity
{

    friend std::ostream& operator<<(std::ostream& o, const Block& block);
    friend std::istream& operator>>(std::istream& i, Block& block);

public:

    Block();
    Block(const short& posX, const short& posY, const short& sizeX, const short& sizeY);
};