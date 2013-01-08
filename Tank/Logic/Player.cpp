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

const short& Player::getFirePosX() const
{
	return firePosX;
}
const short& Player::getFirePosY() const
{
	return firePosY;
}

void Player::setSelected(Tank* const selected)
{
    this->selected = selected;
}

void Player::setFirePosX(const short& posX)
{
	this->firePosX = posX;
}

void Player::setFirePosY(const short& posY)
{
	this->firePosY = posY;
}

void Player::addTank(Tank* const tank)
{
    tanks.push_back(tank);
}

void Player::addInitialTanks()
{

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
	o.write((char*) &firePosX, sizeof(short));
	o.write((char*) &firePosY, sizeof(short));

    serializePointerContainer(tanks.cbegin(), tanks.cend(), o, TankChangedPredicate());

    return o;
}

std::ostream& operator<<(std::ostream& o, const Player& player)
{
    size_t stringSize = player.name.size();

    o.write((char*) &stringSize, sizeof(str_size_t));
    o.write(player.name.c_str(), player.name.size());
	o.write((char*) &player.firePosX, sizeof(short));
	o.write((char*) &player.firePosY, sizeof(short));

    serializePointerContainer(player.tanks.cbegin(), player.tanks.cend(), o);

    return o;
}

std::istream& operator>>(std::istream& in, Player& player)
{
    clearPointerContainer(player.tanks);

    str_size_t stringSize;

    in.read((char*) &stringSize, sizeof(str_size_t));

    char* text = new char[stringSize + 1];

    in.read(text, stringSize);
    text[stringSize] = 0;

    player.name = std::string(text);

	in.read((char*) &player.firePosX, sizeof(short));
	in.read((char*) &player.firePosY, sizeof(short));

    deserializePointerContainer<Tank>(player.tanks, in);

    return in;
}