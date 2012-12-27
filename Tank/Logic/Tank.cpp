#include "Tank.h"
#include "TankTypes.h"

Tank::Tank() {
	init();
}

Tank::Tank(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY, const size_t& typeID)
	: AbstractEntity(posX, posY, sizeX, sizeY) {

	this->typeID = typeID;
	init();
}

void Tank::init() {
	selected = false;
	
	HP = TankTypes::getInstance().getTypes().at(0).HP;
	fireDamage = TankTypes::getInstance().getTypes().at(0).fireDamage;
}

bool Tank::isSelected() const {
	return selected;
}

const short& Tank::getHP() const {
	return HP;
}

const size_t& Tank::getTypeID() const {
	return typeID;
}

const size_t& Tank::getDirX() const {
	return dirX;
}
const size_t& Tank::getDirY() const {
	return dirY;
}

const unsigned short& Tank::getFireDamage() const {
	return fireDamage;
}

void Tank::setSelected(const bool& selected) {
	this->selected = selected;
}

void Tank::setHP(const short& HP) {
	this->HP = HP;
}

void Tank::setDirX(const size_t& dirX) {
	this->dirX = dirX;
}

void  Tank::setDirY(const size_t& dirY) {
	this->dirY = dirY;
}

void Tank::move(const int& dirX, const int& dirY) {
	this->posX += dirX;
	this->posY += dirY;
}

void Tank::fire(int& dirX, int& dirY, size_t& damage) const {
	dirX = this->dirX;
	dirY = this->dirY;
	damage = this->fireDamage;
}

bool Tank::hit(const size_t& damage) {
	this->HP -= damage;

	return HP <= 0;
}