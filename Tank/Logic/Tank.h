#pragma once

#include "AbstractEntity.h"

class Tank : public AbstractEntity
{

    friend std::ostream& operator<<(std::ostream& o, Tank& tank);
    friend std::istream& operator>>(std::istream& i, Tank& tank);

public:

    Tank();
    Tank(const short& posX, const short& posY, const short& sizeX, const short& sizeY, const short& ID, const short& typeID);

    bool isSelected() const;
    bool isChanged() const;
    bool isFiring() const;
    bool isMotion() const;
    const short& getHP() const;
    const short& getTypeID() const;
    const short& getDestinationX() const;
    const short& getDestinationY() const;
    const float& getTankAngle() const;
    const float& getCannonAngle() const;
    const unsigned short& getFireDamage() const;

    void setSelected(const bool& selected);
    void setChanged(const bool& changed);
    void setHP(const short& HP);
    void setFiring(const bool& firing);
    void setMotion(const bool& motion);

    void setDestinationX(const short& dirX);
    void setDestinationY(const short& dirY);

    void setTankAngle(const float& angle);
    void setCannonAngle(const float& angle);

    void move(const short& dirX, const short& dirY);
    bool hit(const short& damage);

private:

    void init();

    short typeID;
    bool selected;
    bool changed;
    bool firing;
    bool motion;
    short destinationX, destinationY;
    float tankAngle, cannonAngle;
    short HP;
    unsigned short fireDamage;
};