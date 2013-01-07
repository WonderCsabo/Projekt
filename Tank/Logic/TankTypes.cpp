#include "TankTypes.h"

TankTypes::TankTypes()
{

    /// TODO: feltölteni ezeket
    types[0] = TankType(100, 10);
}

const TankTypes& TankTypes::getInstance()
{
    static TankTypes instance;

    return instance;
}

const std::unordered_map<short, TankTypes::TankType>& TankTypes::getTypes() const
{
    return types;
}


TankTypes::TankType::TankType(const short& HP, const unsigned short& fireDamage) : HP(HP), fireDamage(fireDamage) { }

TankTypes::TankType::TankType() { }