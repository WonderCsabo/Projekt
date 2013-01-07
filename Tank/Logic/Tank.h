#pragma once

#include "AbstractEntity.h"

class Tank : public AbstractEntity
{

    friend std::ostream& operator<<(std::ostream& o, Tank& tank);
    friend std::istream& operator>>(std::istream& i, Tank& tank);

public:

    Tank();
    Tank(const short& posX, const short& posY, const short& sizeX, const short& sizeY, const short& typeID);

    bool isSelected() const;
    bool isChanged() const;
    const short& getHP() const;
    const short& getTypeID() const;
    const short& getDirX() const;
    const short& getDirY() const;
    const unsigned short& getFireDamage() const;

    void setSelected(const bool& selected);
    void setChanged(const bool& changed);
    void setHP(const short& HP);

    void setDirX(const short& dirX);
    void setDirY(const short& dirY);

    void move(const short& dirX, const short& dirY);
    void fire(short& dirX, short& dirY, short& damage) const;
    bool hit(const short& damage);

private:

    void init();

    short typeID;
    bool selected;
    bool changed;
    short dirX, dirY;
    short HP;
    unsigned short fireDamage;
};