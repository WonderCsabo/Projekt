#pragma once

#include <vector>
#include "Block.h"

class Map {

public:

	Map(const size_t& sizeX, const size_t& sizeY, std::vector<const Block*> blocks = std::vector<const Block*>());
	~Map();

	const std::vector<const Block*> getBlocks() const;
	const size_t& getSizeX() const;
	const size_t& getSizeY() const;

	void add(const Block* const block);
	
private:

	size_t sizeX, sizeY;

	std::vector<const Block*> blocks;

	void initBlocks();
};