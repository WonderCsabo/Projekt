#include "Block.h"

Block::Block() : AbstractEntity() { }

Block::Block(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY) : AbstractEntity(posX, posY, sizeX, sizeY) { }