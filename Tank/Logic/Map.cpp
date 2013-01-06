#include "Map.h"
#include "../Util/Utils.h"

typedef std::string::size_type str_size_t;

Map::Map() { }

Map::Map(const size_t& sizeX, const size_t& sizeY, std::vector<const Block*> blocks) : sizeX(sizeX), sizeY(sizeY), blocks(blocks)
{

    if(blocks.size() == 0)
        initBlocks();
}

Map::~Map()
{

    clearPointerContainer(blocks);
}

const std::vector<const Block*>& Map::getBlocks() const
{
    return blocks;
}

const std::vector<Player*>& Map::getPlayers() const
{
    return players;
}

const size_t& Map::getSizeX() const
{
    return sizeX;
}

const size_t& Map::getSizeY() const
{
    return sizeY;
}

void Map::add(const Block* const block)
{
    blocks.push_back(block);
}

void Map::add(Player* const player)
{
    players.push_back(player);
}

void Map::initBlocks()
{

    /// TODO: feltölteni akadályokkal
    blocks.push_back(new Block(10, 10, 10, 10));
}

std::ostream& operator<<(std::ostream& o, const Map& map)
{

    o.write((char*) &map.sizeX, sizeof(size_t));
    o.write((char*) &map.sizeY, sizeof(size_t));

    serializePointerContainer(map.blocks.cbegin(), map.blocks.cend(), o);

    serializePointerContainer(map.players.cbegin(), map.players.cend(), o);

    return o;
}

std::istream& operator>>(std::istream& in, Map& map)
{

    clearPointerContainer(map.blocks);
    clearPointerContainer(map.players);

    in.read((char*) &map.sizeX, sizeof(size_t));
    in.read((char*) &map.sizeY, sizeof(size_t));

    deserializePointerContainer<Block>(map.blocks, in);

    deserializePointerContainer<Player>(map.players, in);

    return in;
}