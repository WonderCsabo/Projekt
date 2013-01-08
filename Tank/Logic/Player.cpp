#include "Player.h"
#include "../Util/Utils.h"

typedef std::string::size_type str_size_t;
short Player::PLAYER_TANKS_COUNT = 7;

Player::Player()
{
    //addInitialTanks();
}

Player::Player(const std::string& name) : name(name)
{
    //addInitialTanks();
}

Player::~Player()
{

    clearPointerContainer(tanks);
}

const std::string& Player::getName() const
{
    return name;
}

std::vector<Tank*>& Player::getTanks()
{
    return tanks;
}

const Tank* const Player::getSelected() const
{
    return selected;
}

void Player::setSelected(Tank* const selected)
{
    this->selected = selected;
}

void Player::addTank(Tank* const tank)
{
    tanks.push_back(tank);
}

void Player::addInitialTanks()
{

    selected = 0;

    /// TODO: hozzáadni tankokat
    tanks.push_back(new Tank(78, 0, 0, 0, 0, 0));
    tanks.push_back(new Tank(78, 0, 0, 0, 1, 0));
    tanks.push_back(new Tank(78, 0, 0, 99, 2, 0));
}

bool Player::TankChangedPredicate::operator()(const Tank& tank)
{
    return tank.isChanged();
}

std::ostream& Player::serializeChanged(std::ostream& o)
{
    size_t stringSize = name.size();

    o.write((char*) &stringSize, sizeof(str_size_t));
    o.write(name.c_str(), name.size());

    serializePointerContainer(tanks.cbegin(), tanks.cend(), o, TankChangedPredicate());

    return o;
}

std::ostream& operator<<(std::ostream& o, const Player& player)
{
    size_t stringSize = player.name.size();

    o.write((char*) &stringSize, sizeof(str_size_t));
    o.write(player.name.c_str(), player.name.size());

    serializePointerContainer(player.tanks.cbegin(), player.tanks.cend(), o);

    return o;
}

std::istream& operator>>(std::istream& in, Player& player)
{
    clearPointerContainer(player.tanks);
    player.selected = 0;

    str_size_t stringSize;

    in.read((char*) &stringSize, sizeof(str_size_t));

    char* text = new char[stringSize + 1];

    in.read(text, stringSize);
    text[stringSize] = 0;

    player.name = std::string(text);

    deserializePointerContainer<Tank>(player.tanks, in);

    return in;
}