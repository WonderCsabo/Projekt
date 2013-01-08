#include "CommonTeamInfo.h"
#include "../Util/Utils.h"

CommonTeamInfo::CommonTeamInfo(unsigned short tId, Player* player) : teamId(tId), player(player)
{
}
void CommonTeamInfo::addTank(CommonTankInfo* t)
{
	myTanks.push_back(t);
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
	player->setSelected(selected->getLogic());
	tank->reSelect();
}
std::vector<CommonTankInfo *>::iterator CommonTeamInfo::getEnd()
{
	return myTanks.end();
}

CommonTeamInfo::~CommonTeamInfo(void)
{
	clearPointerContainer(myTanks);
}
