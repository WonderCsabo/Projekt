#include "Player.h"

Player::Player(const std::string& name) : name(name), selected(0) { }

Player::~Player() {
	
	while(!tanks.empty()) {
		delete tanks.back();
		tanks.pop_back();
	}
}

const std::string& Player::getName() const {
	return name;
}

const std::vector<Tank*> Player::getTanks() const {
	return tanks;
}

const Tank* const Player::getSelected() const {
	return selected;
}

void Player::setSelected(Tank* const selected) {
	this->selected = selected;
}

void Player::addInitialTanks() {

	/// TODO: hozzáadni tankokat
	tanks.push_back(new Tank(0, 0, 0, 0, 0));
}