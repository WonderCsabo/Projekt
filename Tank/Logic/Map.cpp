#include "Map.h"
#include "../Util/Utils.h"

short Map::BLOCKS_COUNT = 10;

Map::Map() { }

Map::Map(const short& sizeX, const short& sizeY, std::vector<const Block*> blocks) : sizeX(sizeX), sizeY(sizeY), blocks(blocks)
{
	if(blocks.empty())
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

const short& Map::getSizeX() const
{
    return sizeX;
}

const short& Map::getSizeY() const
{
    return sizeY;
}

void Map::add(const Block* const block)
{
    blocks.push_back(block);
}

void Map::add(Player* player)
{
    players.push_back(player);

	for(int i = 0; i < Player::PLAYER_TANKS_COUNT; ++i)
	{
		short posX = std::rand() % 630 + 30;
		short posY = std::rand() % 630 + 30;
		while(getTankOnPosition(posX, posY, 0) || getBlockOnPosition(posX, posY))
		{
			posX = std::rand() % 630 + 30;
			posY = std::rand() % 630 + 30;
		}
		Tank* tank  = new Tank(posX, posY, 35, 35, i, 0);
		player->addTank(tank);
	}
}

void Map::updatePlayer(Player* const player)
{
	for(unsigned int i = 0; i < players.size(); ++i)
	{
		if(player->getName() == players[i]->getName())
		{
			Player* thisPlayer = players[i];

			for(unsigned int j = 0; j < player->getTanks().size(); ++j)
			{
				Tank* updatedTank = player->getTanks()[j];
				
				delete thisPlayer->getTanks()[updatedTank->getID()];
				thisPlayer->getTanks()[player->getTanks()[j]->getID()] = updatedTank;
			}

			return;
		}
	}
}

void Map::initBlocks()
{
	for(int i = 0; i < BLOCKS_COUNT; ++i)
	{
		short posX = std::rand() % 630 + 30;
		short posY = std::rand() % 630 + 30;

		while(getBlockOnPosition(posX, posY))
		{
			posX = std::rand() % 630 + 30;
			posY = std::rand() % 630 + 30;
		}

		add(new Block(posX, posY, 35, 35));
	}
}

const AbstractEntity* Map::isEntityOnPosition(const AbstractEntity* entity, const short& entityPosX, const short& entityPosY, const short& posX, const short& posY, const short& bounds) const
{
	short left = entityPosX - entity->getSizeX() / 2 - bounds;
	short right = entityPosX + entity->getSizeX() / 2 + bounds;
	short top = entityPosY - entity->getSizeY() / 2 - bounds;
	short bottom = entityPosY + entity->getSizeY() / 2 + bounds;

	if(left < posX && right > posX && top < posY && bottom > posY)
		return entity;
	return 0;
}

Tank* Map::getTankOnPosition(const short& posX, const short& posY, Tank* thisTank) const
{
	for(auto playerIter = players.cbegin(); playerIter != players.cend(); ++playerIter)

		for(auto tankIter = (*playerIter)->getTanks().cbegin(); tankIter != (*playerIter)->getTanks().cend(); ++tankIter)

			if(thisTank != *tankIter && isEntityOnPosition(*tankIter, (*tankIter)->getPosX(), (*tankIter)->getPosY(), posX, posY, 20))
				return *tankIter;

	return 0;
}

const Block* Map::getBlockOnPosition(const short& posX, const short& posY) const
{
	for(auto it = blocks.cbegin(); it != blocks.cend(); ++it)
		if(isEntityOnPosition(*it, (*it)->getPosX(), (*it)->getPosY(), posX, posY, 20))
			return *it;

	return 0;
}

std::ostream& operator<<(std::ostream& o, const Map& map)
{

    o.write((char*) &map.sizeX, sizeof(short));
    o.write((char*) &map.sizeY, sizeof(short));

    serializePointerContainer(map.blocks.cbegin(), map.blocks.cend(), o);

    serializePointerContainer(map.players.cbegin(), map.players.cend(), o);

    return o;
}

std::istream& operator>>(std::istream& in, Map& map)
{

    clearPointerContainer(map.blocks);
    clearPointerContainer(map.players);

    in.read((char*) &map.sizeX, sizeof(short));
    in.read((char*) &map.sizeY, sizeof(short));

    deserializePointerContainer<Block>(map.blocks, in);

    deserializePointerContainer<Player>(map.players, in);

    return in;
}