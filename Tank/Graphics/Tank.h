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
	unsigned short team;//k�rlek, k�rlek ne random sz�m legyen, hanem null�t�l n�vekedjen
	Tank(void);
	~Tank(void);
};

