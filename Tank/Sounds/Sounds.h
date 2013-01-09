#pragma once
#include <vector>
#include <SFML/Audio.hpp>
class Sounds
{
private:
    std::vector<sf::SoundBuffer*> bummBuffers;
    sf::SoundBuffer backgroundBuffer;
    std::vector<sf::Sound*> bumms;
    sf::Sound background;
    unsigned short stage;
    void addBackground(std::string);
    void addBumm(std::string);
public:
    Sounds(void);
    ~Sounds(void);
    void playBumm();
};

