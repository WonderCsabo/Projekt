#pragma once

#include "../Graphics/AbstractView.h"
#include "../Graphics/TextureHolder.h"
#include "../Util/DebugWindow.h"
#include <string>
#include <vector>

class View :
	public AbstractView
{
public:
	void drawEverything();
	void addBarrel(float, float, float, float);
	View(sf::RenderWindow *, bool);
	View(sf::RenderWindow *rw);
	~View(void);
private:
	void drawBarrels();
	void init();
	std::vector<sf::Sprite*> barrels;
	DebugWindow debugWindow;
	TextureHolder barrelTextures;
	void drawDebug();
	void clearBackground();
	sf::RectangleShape *debugBox;
	sf::Text *debug;
};

