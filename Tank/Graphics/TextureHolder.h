#include <vector>
#include <SFML/Graphics.hpp>
#pragma once
class TextureHolder
{
private:
	std::vector<sf::Texture*> textures;
public:
	void addTexture(sf::Texture*);
	sf::Texture* returnRandom();
	TextureHolder(void);
	void clear();
	~TextureHolder(void);
};

