#pragma once

#include <cstddef>
#include <iostream>

class AbstractEntity
{

	friend std::ostream& operator<<(std::ostream& o, const AbstractEntity& abstractEntity);
	friend std::istream& operator>>(std::istream& i, AbstractEntity& abstractEntity);

protected:

	AbstractEntity();
	AbstractEntity(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY);
	virtual ~AbstractEntity();

	virtual void init();

public:

	const size_t& getPosX() const;
	const size_t& getPosY() const;
	const size_t& getSizeX() const;
	const size_t& getSizeY() const;

	void setPosX(const size_t& posX);
	void setPosY(const size_t& posY);
	void setSizeX(const size_t& sizeX);
	void setSizeY(const size_t& sizeY);

	const size_t& getID() const;

	static const size_t& getEntityCount();

protected:

	size_t posX, posY;
	size_t sizeX, sizeY;

	size_t ID;

	static size_t entityCount, IDCount;
};


