#include "Player.h"
#include "../Util/Utils.h"

typedef std::vector<Tank*>::size_type vec_size_t;
typedef std::string::size_type str_size_t;

Player::Player() {
	addInitialTanks();
}

Player::Player(const std::string& name) : name(name) {
	addInitialTanks();
}

Player::~Player() {
	
	clearPointerContainer(tanks);
}

const std::string& Player::getName() const {
	return name;
}

const std::vector<Tank*>& Player::getTanks() const {
	return tanks;
}

const Tank* const Player::getSelected() const {
	return selected;
}

void Player::setSelected(Tank* const selected) {
	this->selected = selected;
}

void Player::addTank(Tank* const tank) {
	tanks.push_back(tank);
}

void Player::addInitialTanks() {

	selected = 0;

	/// TODO: hozzáadni tankokat
	tanks.push_back(new Tank(78, 0, 0, 0, 0));
	tanks.push_back(new Tank(78, 0, 0, 0, 0));
	tanks.push_back(new Tank(78, 0, 0, 99, 0));
}

std::ostream& operator<<(std::ostream& o, const Player& player) {
	size_t stringSize = player.name.size();

	o.write((char*) &stringSize, sizeof(str_size_t));
	o.write(player.name.c_str(), player.name.size());

	vec_size_t numOfTanks = player.tanks.size();
	o.write((char*) &numOfTanks, sizeof(vec_size_t));

	for(vec_size_t i = 0; i < numOfTanks; ++i) 
		o << *player.tanks[i];

	return o;
}

std::istream& operator>>(std::istream& in, Player& player) {

	clearPointerContainer(player.tanks);
	player.selected = 0;

	str_size_t stringSize;

	in.read((char*) &stringSize, sizeof(str_size_t));

	char* text = new char[stringSize + 1];

	in.read(text, stringSize);
	text[stringSize] = 0;

	player.name = std::string(text);

	vec_size_t numOfTanks = 0;
	in.read((char*) &numOfTanks, sizeof(vec_size_t));

	for(vec_size_t i = 0; i < numOfTanks; ++i) {

		Tank* t = new Tank();
		in >> *t;
		player.tanks.push_back(t);
	}

	return in;
}