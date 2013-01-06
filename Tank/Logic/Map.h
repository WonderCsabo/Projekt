#pragma once

#include <vector>
#include <iostream>
#include "Block.h"
#include "Player.h"

class Map
{

    friend std::ostream& operator<<(std::ostream& o, const Map& map);
    friend std::istream& operator>>(std::istream& i, Map& map);

public:

    Map();
    Map(const size_t& sizeX, const size_t& sizeY, std::vector<const Block*> blocks = std::vector<const Block*>());
    ~Map();

    const std::vector<const Block*>& getBlocks() const;
    const std::vector<Player*>& getPlayers() const;
    const size_t& getSizeX() const;
    const size_t& getSizeY() const;

    void add(const Block* const block);
    void add(Player* const player);

private:

    size_t sizeX, sizeY;

    std::vector<const Block*> blocks;
    std::vector<Player*> players;

    void initBlocks();
};