#include "Map.h"

Map::Map(const size_t& sizeX, const size_t& sizeY, std::vector<const Block*> blocks) : sizeX(sizeX), sizeY(sizeY), blocks(blocks) {
	initBlocks();
}

Map::~Map() {

	while(!blocks.empty()) {
		delete blocks.back();
		blocks.pop_back();
	}

}

const std::vector<const Block*> Map::getBlocks() const {
	return blocks;
}

const size_t& Map::getSizeX() const {
	return sizeX;
}

const size_t& Map::getSizeY() const {
	return sizeY;
}

void Map::add(const Block* const block) {
	blocks.push_back(block);
}

void Map::initBlocks() {

	/// TODO: feltölteni akadályokkal
	blocks.push_back(new Block(10, 10, 10, 10));
}