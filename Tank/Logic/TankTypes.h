#pragma once

#include <unordered_map>
#include <cstddef>

class TankTypes
{

public:

    static const TankTypes& getInstance();

    struct TankType
    {

        TankType();
        TankType(const short& HP, const unsigned short& fireDamage);

        short HP;
        unsigned short fireDamage;
    };

    const std::unordered_map<size_t, TankType>& getTypes() const;

private:

    TankTypes();
    TankTypes(const TankTypes&);
    TankTypes& operator=(const TankTypes&);

    std::unordered_map<size_t, TankType> types;
};
