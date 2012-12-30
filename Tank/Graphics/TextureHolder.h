#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class TextureHolder
{
private:
	std::vector<sf::Texture*> textures;
public:
	TextureHolder(void);
	~TextureHolder(void);
	void addTexture(sf::Texture*);
	sf::Texture* returnRandom();
	sf::Texture* returnIndex(int);;
};

