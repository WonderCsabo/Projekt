#include "CommonTeamInfo.h"
#include "../Util/Utils.h"

CommonTeamInfo::CommonTeamInfo(unsigned short tId) : teamId(tId)
{
}
void CommonTeamInfo::addTank(CommonTankInfo* t)
{
	myTanks.push_back(t);
	if(myTanks.size() == 1)
	{
		selected = t;
		selected->deSelect();
	}
}
std::vector<CommonTankInfo *>::iterator CommonTeamInfo::getBegin()
{
	return myTanks.begin();
}

CommonTankInfo* CommonTeamInfo::getSelected()
{
	return selected;
}
void CommonTeamInfo::setSelected(CommonTankInfo* tank)
{

	selected = tank;
}
std::vector<CommonTankInfo *>::iterator CommonTeamInfo::getEnd()
{
	return myTanks.end();
}

CommonTeamInfo::~CommonTeamInfo(void)
{
	clearPointerContainer(myTanks);
}
