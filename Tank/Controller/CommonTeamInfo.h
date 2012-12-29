#pragma once
#include "CommonTankInfo.h"
#include <vector>
class CommonTeamInfo
{
private:
	const unsigned short teamId;
	std::vector<CommonTankInfo *> myTanks;
	CommonTankInfo* selected;
public:
	std::vector<CommonTankInfo *>::iterator getBegin();
	std::vector<CommonTankInfo *>::iterator getEnd();
	CommonTankInfo* getSelected();
	void setSelected(CommonTankInfo*);
	void addTank(CommonTankInfo*);
	CommonTeamInfo(unsigned short);
	~CommonTeamInfo(void);
};

