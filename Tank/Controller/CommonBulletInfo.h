#pragma once
#include <SFML/Graphics.hpp>
class CommonBulletInfo
{
private:
	sf::Vector2f position;
	sf::Vector2f destination;
public:
	const sf::Vector2f& getPosition();
	const sf::Vector2f& getDestination();
	void setPosition(const sf::Vector2f&);
	void setDestination(const sf::Vector2f&);
	CommonBulletInfo(sf::Vector2f,sf::Vector2f);
	~CommonBulletInfo(void);
};

