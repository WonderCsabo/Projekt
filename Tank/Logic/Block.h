#pragma once

#include "AbstractEntity.h"

class Block : public AbstractEntity {

public:

	Block();
	Block(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY);
};