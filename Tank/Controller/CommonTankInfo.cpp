#include "CommonTankInfo.h"
CommonTankInfo::CommonTankInfo(unsigned short t):teamValue(t) {}
unsigned short CommonTankInfo::team()
{
	return teamValue;
}
CommonTankInfo::~CommonTankInfo(void) {}