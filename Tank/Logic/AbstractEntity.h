#pragma once

class AbstractEntity {

protected:

	AbstractEntity();
	AbstractEntity(const size_t& posX, const size_t& posY, const size_t& sizeX, const size_t& sizeY);
	virtual ~AbstractEntity();

public:

	const size_t& getPosX() const;
	const size_t& getPosY() const;
	const size_t& getSizeX() const;
	const size_t& getSizeY() const;

	void setPosX(const size_t& posX);
	void setPosY(const size_t& posY);
	void setSizeX(const size_t& sizeX);
	void setSizeY(const size_t& sizeY);

	static const size_t& getEntityCount();

private:

	size_t posX, posY;
	size_t sizeX, sizeY;

	static size_t entityCount;
};