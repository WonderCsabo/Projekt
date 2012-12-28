#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class TextureHolder
{
private:
  std::vector<sf::Texture*> textures;
public:
  void addTexture(sf::Texture*);
  sf::Texture* returnRandom();
  sf::Texture* returnIndex(int);
  TextureHolder(void);
  void clear();
  ~TextureHolder(void);
};

