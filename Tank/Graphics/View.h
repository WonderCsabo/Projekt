#pragma once
#include "../Graphics/abstractview.h"
#include "../Graphics/TextureHolder.h"
#include "../Controller/CommonTankInfo.h"
#include "../Graphics/TankAnimation.h"
#include "../Util/DebugWindow.h"
#include <string>
#include <vector>
class View :
    public AbstractView
{
public:

    View(sf::RenderWindow *rw);
    ~View(void);

    /*Initalization of the map*/
    /*Creates the barrel sprites on the specific position, with the give size.*/
    void addBarrel(const sf::Vector2f&,const sf::Vector2f&);
    /*Creates the tank sprites and initalize them with the given infos.
    CommonTankinfo* - stored in a vector. Every change applyed on the object apperas on screen.*/
    void addTank(CommonTankInfo*);

    /*Refreshes the screen.*/
    void drawEverything();


private:
    void init();
    void updateTanks();
    void drawTank();
    void drawBarrels();
    void drawInputChat();
    void drawOutputChat();
    void clearBackground();
    sf::Texture mapTexture;
    sf::Sprite mapSprite;

    TextureHolder barrelTextures;
    std::vector<sf::Sprite*> barrels;//Handled

    TextureHolder *tankTextures;//Handled
    TextureHolder *bummTextures;//Handled
    std::vector<TankAnimation*> tanks;//Handled

    sf::Texture* selection;//Handled
    sf::Texture* cannonTexture;//Handled
    sf::Texture* bulletTexture;//Handled
    std::vector<sf::Color> teamColors;

    sf::RectangleShape inputChatBackground;
    sf::RectangleShape outputChatBackground;
    sf::Text inputChatText;
    sf::Text outputChatText;

};
