#include "Block.h"

Block::Block() : AbstractEntity() { }

Block::Block(const short& posX, const short& posY, const short& sizeX, const short& sizeY) : AbstractEntity(posX, posY, sizeX, sizeY) { }

std::ostream& operator<<(std::ostream& o, const Block& block)
{
    o << dynamic_cast<const AbstractEntity&>(block);

    return o;
}

std::istream& operator>>(std::istream& i, Block& block)
{
    i >> dynamic_cast<AbstractEntity&>(block);

    return i;
}