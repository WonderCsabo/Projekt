#pragma once
#include "CommonTankInfo.h"
#include "../Logic/Player.h"
#include <vector>
class CommonTeamInfo
{
private:
	const unsigned short teamId;
	std::vector<CommonTankInfo *> myTanks;
	CommonTankInfo* selected;
	Player* player;

public:
	std::vector<CommonTankInfo *>::iterator getBegin();
	std::vector<CommonTankInfo *>::iterator getEnd();
	CommonTankInfo* getSelected();
	void setSelected(CommonTankInfo*);
	void addTank(CommonTankInfo*);
	sf::Vector2f getFirePos() const;
	void setFirePos(const sf::Vector2f&);
	CommonTeamInfo(unsigned short, Player*);
	~CommonTeamInfo(void);
};

