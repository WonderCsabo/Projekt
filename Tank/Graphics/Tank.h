#pragma once
class Tank
{
public:
	float posX;
	float posY;
	float width;
	float height;
	float orientation;
	float canonOrientation;
	unsigned short team;//kérlek, kérlek ne random szám legyen, hanem nullától növekedjen
	Tank(void);
	~Tank(void);
};

