#include "Map.h"
#include "../Util/Utils.h"

typedef std::vector<Block*>::size_type vec_size_t;
typedef std::string::size_type str_size_t;

Map::Map(const size_t& sizeX, const size_t& sizeY, std::vector<const Block*> blocks) : sizeX(sizeX), sizeY(sizeY), blocks(blocks) {
	initBlocks();
}

Map::~Map() {

	clearPointerContainer(blocks);
}

const std::vector<const Block*>& Map::getBlocks() const {
	return blocks;
}

const std::vector<Player*>& Map::getPlayers() const {
	return players;
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

void Map::add(Player* const player) {
	players.push_back(player);
}

void Map::initBlocks() {

	/// TODO: feltölteni akadályokkal
	blocks.push_back(new Block(10, 10, 10, 10));
}

std::ostream& operator<<(std::ostream& o, const Map& map) {

	o.write((char*) &map.sizeX, sizeof(size_t));
	o.write((char*) &map.sizeY, sizeof(size_t));

	vec_size_t numOfBlocks = map.blocks.size();
	o.write((char*) &numOfBlocks, sizeof(vec_size_t));

	for(vec_size_t i = 0; i < numOfBlocks; ++i) 
		o << *map.blocks[i];

	vec_size_t numOfPlayers = map.players.size();
	o.write((char*) &numOfPlayers, sizeof(vec_size_t));

	for(vec_size_t i = 0; i < numOfPlayers; ++i) 
		o << *map.players[i];

	return o;
}

std::istream& operator>>(std::istream& in, Map& map) {

	clearPointerContainer(map.blocks);
	clearPointerContainer(map.players);

	in.read((char*) &map.sizeX, sizeof(size_t));
	in.read((char*) &map.sizeY, sizeof(size_t));

	vec_size_t numOfBlocks = map.blocks.size();
	in.read((char*) &numOfBlocks, sizeof(vec_size_t));

	for(vec_size_t i = 0; i < numOfBlocks; ++i) {

		Block* b = new Block();
		in >> *b;
		map.blocks.push_back(b);
	}

	vec_size_t numOfPlayers = map.players.size();
	in.read((char*) &numOfPlayers, sizeof(vec_size_t));

	for(vec_size_t i = 0; i < numOfPlayers; ++i) {

		Player* p = new Player();
		in >> *p;
		map.players.push_back(p);
	}

	return in;
}