#include "AbstractEntity.h"

AbstractEntity::AbstractEntity() {
	init();
}

AbstractEntity::AbstractEntity(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY) {
	init();
	this->posX = posX;
	this->posY = posY;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

AbstractEntity::~AbstractEntity() {
	--entityCount;
}

const size_t& AbstractEntity::getPosX() const {
	return posX;
}

const size_t& AbstractEntity::getPosY() const {
	return posY;
}

const size_t& AbstractEntity::getSizeX() const {
	return sizeX;
}

const size_t& AbstractEntity::getSizeY() const {
	return sizeY;
}

void AbstractEntity::setPosX(const size_t& posX) {
	this->posX = posX;
}

void AbstractEntity::setPosY(const size_t& posY) {
	this->posY = posY;
}

void AbstractEntity::setSizeX(const size_t& sizeX) {
	this->sizeX = sizeX;
}

void AbstractEntity::setSizeY(const size_t& sizeY) {
	this->sizeY = sizeY;
}

const size_t& AbstractEntity::getEntityCount() {
	return entityCount;
}

void AbstractEntity::init() {
	++entityCount;
	++IDCount;
	ID = IDCount;
}

size_t AbstractEntity::entityCount = 0;
size_t AbstractEntity::IDCount = 0;