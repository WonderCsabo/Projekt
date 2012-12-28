#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <functional>
#include "Graphics/View.h"
#include "Graphics/AbstractView.h"
#include "Net/Client.h"
#include "GUI/StartGui.h"
#include "Util/DebugWindow.h"
#include "Util/GetInput.h"
#include "Util/Os.h"

class Controller
{
private:
  std::vector<CommonTankInfo*> tanks;
  sf::RenderWindow *window;
  AbstractView *view;
  sf::Event event;
public:
  Controller(short x, short y, std::string);
  ~Controller(void);
  Client* startgui();
  void addRandomBarrels(AbstractView* v);
  void addTanks(AbstractView* v);
  sf::RenderWindow* getWindow();
  AbstractView* getView();
  bool programRunning();
  sf::Event getEvent();
  bool pollEvent();
  void addText(sf::Text);
  void shutDown();
  void refresh();
};

