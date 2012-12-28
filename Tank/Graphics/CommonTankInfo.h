#pragma once
/*A megjelen�t�s erre alapul, ez a k�z�s pont, az adapter.
El�g besz�desre siker�ltek szerintem a tagv�ltoz�k nevei.
Hogyha ezekb�l b�rmit m�dos�totok, akkor az l�that�v� v�lik egyb�l a k�perny�n.
Egyed�l akkor nem, hogyha a csapatot m�dos�tj�tok, ugye ez grafik�ban csak egy sz�nt jelent,
ami inicializ�l�skor �ll�todik be, egy v�lelenszer�re. Ez�rt nincs hozz� setter*/
class CommonTankInfo
{
private:
  const unsigned short teamValue;//k�rlek, k�rlek ne random sz�m legyen, hanem null�t�l n�vekedjen
public:
  unsigned short team();
  float posX;
  float posY;
  float width;
  float height;
  float orientation;
  float cannonOrientation;
  bool selected;
  CommonTankInfo(unsigned short);
  ~CommonTankInfo(void);
};

