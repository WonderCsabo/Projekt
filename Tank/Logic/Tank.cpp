#include "Tank.h"
#include "TankTypes.h"

Tank::Tank() : destinationX(0), destinationY(0), motion(true)
{
    init();
}

Tank::Tank(const short& posX, const short& posY, const short& sizeX, const short& sizeY, const short& ID, const short& typeID)
	: AbstractEntity(posX, posY, sizeX, sizeY), typeID(typeID), destinationX(0), destinationY(0), tankAngle(0), cannonAngle(0),
	selected(0), firing(0), changed(0), motion(false)
{
	this->ID = ID;
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

bool Tank::isFiring() const
{
	return firing;
}

bool Tank::isMotion() const
{
	return motion;
}

const short& Tank::getHP() const
{
    return HP;
}

const short& Tank::getTypeID() const
{
    return typeID;
}

const short& Tank::getDestinationX() const
{
	return destinationX;
}

const short& Tank::getDestinationY() const
{
	return destinationY;
}

const float& Tank::getTankAngle() const
{
	return tankAngle;
}

const float& Tank::getCannonAngle() const
{
	return cannonAngle;
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

void Tank::setFiring(const bool& firing)
{
	this->firing = firing;
	changed = true;
}

void Tank::setMotion(const bool& motion)
{
	this->motion = motion;
	changed = true;
}

void Tank::setDestinationX(const short& destinationX)
{
	this->destinationX = destinationX;
    changed = true;
}

void  Tank::setDestinationY(const short& destinationY)
{
    this->destinationY = destinationY;
    changed = true;
}

void Tank::setTankAngle(const float& angle)
{
	tankAngle = angle;
	changed = true;
}
void Tank::setCannonAngle(const float& angle)
{
	cannonAngle = angle;
	changed = true;
}

void Tank::move(const short& destinationX, const short& destinationY)
{
    this->posX += destinationX;
    this->posY += destinationY;
    changed = true;
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

    o.write((char*) &tank.destinationX, sizeof(short));
    o.write((char*) &tank.destinationY, sizeof(short));
    o.write((char*) &tank.typeID, sizeof(short));
	o.write((char*) &tank.tankAngle, sizeof(float));
	o.write((char*) &tank.cannonAngle, sizeof(float));
	o.write((char*) &tank.firing, sizeof(bool));

    return o;
}

std::istream& operator>>(std::istream& i, Tank& tank)
{
    i >> dynamic_cast<AbstractEntity&>(tank);

    i.read((char*) &tank.destinationX, sizeof(short));
    i.read((char*) &tank.destinationY, sizeof(short));
    i.read((char*) &tank.typeID, sizeof(short));
	i.read((char*) &tank.tankAngle, sizeof(float));
	i.read((char*) &tank.cannonAngle, sizeof(float));
	i.read((char*) &tank.firing, sizeof(bool));

    return i;
}