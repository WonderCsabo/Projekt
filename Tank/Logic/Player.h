#pragma once

#include <string>
#include <vector>
#include "Tank.h"

class Player {

public:

	Player(const std::string& name);
	~Player();

	const std::string& getName() const;
	const std::vector<Tank*> getTanks() const;
	const Tank* const getSelected() const;

	void setSelected(Tank* const selected);

private:

	std::string name;
	std::vector<Tank*> tanks;
	Tank* selected;

	void addInitialTanks();
};