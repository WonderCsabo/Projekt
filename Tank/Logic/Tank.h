#pragma once

#include "AbstractEntity.h"

class Tank : public AbstractEntity
{

	friend std::ostream& operator<<(std::ostream& o, const Tank& tank);
	friend std::istream& operator>>(std::istream& i, Tank& tank);

public:

	Tank();
	Tank(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY, const size_t& typeID);

	bool isSelected() const;
	const short& getHP() const;
	const size_t& getTypeID() const;
	const size_t& getDirX() const;
	const size_t& getDirY() const;
	const unsigned short& getFireDamage() const;

	void setSelected(const bool& selected);
	void setHP(const short& HP);

	void setDirX(const size_t& dirX);
	void setDirY(const size_t& dirY);

	void move(const int& dirX, const int& dirY);
	void fire(int& dirX, int& dirY, size_t& damage) const;
	bool hit(const size_t& damage);

private:

	void init();

	size_t typeID;
	bool selected;
	size_t dirX, dirY;
	short HP;
	unsigned short fireDamage;
};