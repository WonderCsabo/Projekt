#include "CommonTeamInfo.h"
#include "../Util/Utils.h"

CommonTeamInfo::CommonTeamInfo(unsigned short tId, Player* player) : teamId(tId), player(player), aliveTanks(Player::PLAYER_TANKS_COUNT)
{
}
void CommonTeamInfo::addTank(CommonTankInfo* t)
{
	myTanks.push_back(t);
}

void CommonTeamInfo::removeTank()
{
	--aliveTanks;
}

bool CommonTeamInfo::isAlive()
{
	return aliveTanks > 0;
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

sf::Vector2f CommonTeamInfo::getFirePos() const
{
	return sf::Vector2f(player->getFirePosX(), player->getFirePosY());
}

void CommonTeamInfo::setFirePos(const sf::Vector2f& pos)
{
	player->setFirePosX((short) pos.x);
	player->setFirePosY((short) pos.y); 
}

std::vector<CommonTankInfo *>::iterator CommonTeamInfo::getEnd()
{
	return myTanks.end();
}

CommonTeamInfo::~CommonTeamInfo(void)
{
	clearPointerContainer(myTanks);
}
