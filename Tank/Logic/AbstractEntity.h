#pragma once

#include <cstddef>
#include <iostream>

class AbstractEntity
{

    friend std::ostream& operator<<(std::ostream& o, const AbstractEntity& abstractEntity);
    friend std::istream& operator>>(std::istream& i, AbstractEntity& abstractEntity);

protected:

    AbstractEntity();
    AbstractEntity(const short& posX, const short& posY, const short& sizeX, const short& sizeY);
    virtual ~AbstractEntity();

    virtual void init();

public:

    const short& getPosX() const;
    const short& getPosY() const;
    const short& getSizeX() const;
    const short& getSizeY() const;

    void setPosX(const short& posX);
    void setPosY(const short& posY);
    void setSizeX(const short& sizeX);
    void setSizeY(const short& sizeY);

    const short& getID() const;

    static const short& getEntityCount();

protected:

    short posX, posY;
    short sizeX, sizeY;

    short ID;

    static short entityCount, IDCount;
};


