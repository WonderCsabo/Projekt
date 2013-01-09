#pragma once

#include <string>
#include <vector>
#include "Tank.h"

class Player
{

    friend std::ostream& operator<<(std::ostream& o, const Player& player);
    friend std::istream& operator>>(std::istream& i, Player& player);

public:

    Player();
    Player(const std::string& name);
    ~Player();

    const std::string& getName() const;
    std::vector<Tank*>& getTanks();
    const Tank* const getSelected() const;
    const short& getFirePosX() const;
    const short& getFirePosY() const;

    void setSelected(Tank* const selected);
    void addTank(Tank* const tank);

    void setFirePosX(const short& posX);
    void setFirePosY(const short& posY);

    struct TankChangedPredicate
    {
        bool operator()(const Tank& tank);
    };

    std::ostream& serializeChanged(std::ostream& o);

    static short PLAYER_TANKS_COUNT;

private:

    std::string name;
    std::vector<Tank*> tanks;
    Tank* selected;
    short firePosX, firePosY;

    void addInitialTanks();
};