#include "AbstractEntity.h"

AbstractEntity::AbstractEntity()
{
    init();
}

AbstractEntity::AbstractEntity(const short& posX, const short& posY, const short& sizeX, const short& sizeY)
    : posX(posX), posY(posY), sizeX(sizeX), sizeY(sizeY)
{

    init();
}

AbstractEntity::~AbstractEntity()
{
    --entityCount;
}

const short& AbstractEntity::getPosX() const
{
    return posX;
}

const short& AbstractEntity::getPosY() const
{
    return posY;
}

const short& AbstractEntity::getSizeX() const
{
    return sizeX;
}

const short& AbstractEntity::getSizeY() const
{
    return sizeY;
}

void AbstractEntity::setPosX(const short& posX)
{
    this->posX = posX;
}

void AbstractEntity::setPosY(const short& posY)
{
    this->posY = posY;
}

void AbstractEntity::setSizeX(const short& sizeX)
{
    this->sizeX = sizeX;
}

void AbstractEntity::setSizeY(const short& sizeY)
{
    this->sizeY = sizeY;
}

const short& AbstractEntity::getEntityCount()
{
    return entityCount;
}

const short& AbstractEntity::getID() const
{
	return ID;
}

void AbstractEntity::init()
{
    ++entityCount;
    ++IDCount;
    ID = IDCount;
}

short AbstractEntity::entityCount = 0;
short AbstractEntity::IDCount = 0;

std::ostream& operator<<(std::ostream& o, const AbstractEntity& abstractEntity)
{
    o.write((char*) &abstractEntity.ID, sizeof(short));
    o.write((char*) &abstractEntity.posX, sizeof(short));
    o.write((char*) &abstractEntity.posY, sizeof(short));
    o.write((char*) &abstractEntity.sizeX, sizeof(short));
    o.write((char*) &abstractEntity.sizeY, sizeof(short));

    return o;
}

std::istream& operator>>(std::istream& i, AbstractEntity& abstractEntity)
{
    i.read((char*) &abstractEntity.ID, sizeof(short));
    i.read((char*) &abstractEntity.posX, sizeof(short));
    i.read((char*) &abstractEntity.posY, sizeof(short));
    i.read((char*) &abstractEntity.sizeX, sizeof(short));
    i.read((char*) &abstractEntity.sizeY, sizeof(short));

    return i;
}