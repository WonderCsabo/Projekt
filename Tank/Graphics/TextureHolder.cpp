#include "TextureHolder.h"
#include "../Util/Utils.h"

#include <cstdlib>
#include <ctime>

TextureHolder::TextureHolder(void)
{
}
void TextureHolder::addTexture(sf::Texture* t)
{
	textures.push_back(t);
}

sf::Texture* TextureHolder::returnRandom()
{
return textures[std::rand()%textures.size()];
}
sf::Texture* TextureHolder::returnIndex(int i)
{
return textures[i];
}


TextureHolder::~TextureHolder(void)
{
	this->clear();
}

void TextureHolder::clear(void)
{
	clearPointerContainer(textures);
}