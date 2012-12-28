#pragma once
#include "CommonTankInfo.h"
#include <SFML/Graphics.hpp>
#include <list>

class AbstractView
{
public:
  AbstractView(sf::RenderWindow *,bool);
  AbstractView(sf::RenderWindow *);
  //A renderwindowt a mainben kell megcsinálni, mert az kell a eseménykezelés miatt ,
  //amit ugye szét kéne választani, mondjuk egy controllba(logika).
  virtual ~AbstractView(void);
  virtual void drawEverything() = 0;
  void addDebugInfo(std::string);
  virtual void addBarrel(float, float, float, float) = 0;
  virtual void addTank(CommonTankInfo*) = 0;
  virtual void addText(sf::Text) = 0;
  virtual void upDateTank(CommonTankInfo*, CommonTankInfo*) = 0;
protected:
  std::list<std::string> debugMessages;
  sf::RenderWindow *window;
  bool debugMode;
};

