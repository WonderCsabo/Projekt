#pragma once
class CommonTankInfo
{
public:
	float posX;
	float posY;
	float width;
	float height;
	float orientation;
	float canonOrientation;
	unsigned short team;//kérlek, kérlek ne random szám legyen, hanem nullától növekedjen
	CommonTankInfo(void);
	~CommonTankInfo(void);
};

