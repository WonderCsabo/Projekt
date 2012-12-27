#pragma once
#include "../Graphics/abstractview.h"
#include "../Graphics/TextureHolder.h"
#include "../Graphics/Tank.h"
#include "../Graphics/TankAnimation.h"

#include <string>
#include <vector>
#include <map>

class View :
	public AbstractView
{
public:
	void drawEverything();
	void addBarrel(float, float, float, float);
	void addTank(Tank*);
	void upDateTank(Tank*, Tank*);
	View(sf::RenderWindow *, bool);
	View(sf::RenderWindow *rw);
	~View(void);
private:
	void drawTank();
	void drawBarrels();
	void init();
	TextureHolder barrelTextures;
	void drawDebug();
	void clearBackground();
	std::vector<sf::Color> teamColors;
	std::vector<TankAnimation*> tanks;
	
	//pointers
	std::vector<sf::Sprite*> barrels;//pipa
	TextureHolder *tankTextures;//pipa
	sf::RectangleShape *debugBox;//pipa
	sf::Text *debug;//pipa
};

