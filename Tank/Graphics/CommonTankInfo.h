#pragma once
class CommonTankInfo
{
public:
  float posX;
  float posY;
  float width;
  float height;
  float orientation;
  float cannonOrientation;
  unsigned short team;//k�rlek, k�rlek ne random sz�m legyen, hanem null�t�l n�vekedjen
  CommonTankInfo(void);
  ~CommonTankInfo(void);
};

