#pragma once
/*A megjelenítés erre alapul, ez a közös pont, az adapter.
Elég beszédesre sikerültek szerintem a tagváltozók nevei.
Hogyha ezekbõl bármit módosítotok, akkor az láthatóvá válik egybõl a képernyõn.
Egyedül akkor nem, hogyha a csapatot módosítjátok, ugye ez grafikában csak egy színt jelent,
ami inicializáláskor állítodik be, egy vélelenszerûre. Ezért nincs hozzá setter*/
class CommonTankInfo
{
private:
  const unsigned short teamValue;//kérlek, kérlek ne random szám legyen, hanem nullától növekedjen
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

