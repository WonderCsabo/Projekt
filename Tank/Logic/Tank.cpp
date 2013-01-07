#include "Tank.h"
#include "TankTypes.h"

Tank::Tank() : dirX(0), dirY(0)
{
    init();
}

Tank::Tank(const short& posX, const short& posY, const short& sizeX, const short& sizeY, const short& typeID)
    : AbstractEntity(posX, posY, sizeX, sizeY), typeID(typeID), dirX(0), dirY(0)
{

    init();
}

void Tank::init()
{
    selected = false;
    changed = false;

    HP = TankTypes::getInstance().getTypes().at(0).HP;
    fireDamage = TankTypes::getInstance().getTypes().at(0).fireDamage;
}

bool Tank::isSelected() const
{
    return selected;
}

bool Tank::isChanged() const
{
    return changed;
}

const short& Tank::getHP() const
{
    return HP;
}

const short& Tank::getTypeID() const
{
    return typeID;
}

const short& Tank::getDirX() const
{
    return dirX;
}

const short& Tank::getDirY() const
{
    return dirY;
}

const unsigned short& Tank::getFireDamage() const
{
    return fireDamage;
}

void Tank::setSelected(const bool& selected)
{
    this->selected = selected;
    changed = true;
}

void Tank::setChanged(const bool& changed)
{
    this->changed = changed;
}

void Tank::setHP(const short& HP)
{
    this->HP = HP;
    changed = true;
}

void Tank::setDirX(const short& dirX)
{
    this->dirX = dirX;
    changed = true;
}

void  Tank::setDirY(const short& dirY)
{
    this->dirY = dirY;
    changed = true;
}

void Tank::move(const short& dirX, const short& dirY)
{
    this->posX += dirX;
    this->posY += dirY;
    changed = true;
}

void Tank::fire(short& dirX, short& dirY, short& damage) const
{
    dirX = this->dirX;
    dirY = this->dirY;
    damage = this->fireDamage;
}

bool Tank::hit(const short& damage)
{
    changed = true;
    this->HP -= damage;

    return HP <= 0;
}

std::ostream& operator<<(std::ostream& o, Tank& tank)
{
    tank.changed = false;

    o << dynamic_cast<const AbstractEntity&>(tank);

    o.write((char*) &tank.dirX, sizeof(short));
    o.write((char*) &tank.dirY, sizeof(short));
    o.write((char*) &tank.typeID, sizeof(short));

    return o;
}

std::istream& operator>>(std::istream& i, Tank& tank)
{
    i >> dynamic_cast<AbstractEntity&>(tank);

    i.read((char*) &tank.dirX, sizeof(short));
    i.read((char*) &tank.dirY, sizeof(short));
    i.read((char*) &tank.typeID, sizeof(short));

    tank.init();

    return i;
}