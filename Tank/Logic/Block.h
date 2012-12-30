#pragma once

#include <iostream>
#include "AbstractEntity.h"

class Block : public AbstractEntity
{

	friend std::ostream& operator<<(std::ostream& o, const Block& block);
	friend std::istream& operator>>(std::istream& i, Block& block);

public:

	Block();
	Block(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY);
};