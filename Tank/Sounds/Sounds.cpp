#include "Sounds.h"

Sounds::Sounds(void)
{
	addBackground("resource/backgroundmusic.wav");
	addBumm("resource/bumm1.wav");
	addBumm("resource/bumm2.wav");
	addBumm("resource/bumm3.wav");
	addBumm("resource/bumm4.wav");
	addBumm("resource/bumm5.wav");
	addBumm("resource/bumm6.wav");
	addBumm("resource/bumm7.wav");
	addBumm("resource/bumm8.wav");
	addBumm("resource/bumm9.wav");
	stage = 0;
	background.play();
}


Sounds::~Sounds(void)
{
}

void Sounds::addBackground(std::string s)
{
	backgroundBuffer.loadFromFile(s);
	background.setBuffer(backgroundBuffer); 
	background.setLoop(true);
	background.setPitch(0.8f);
	background.setVolume(75.f);
}
void Sounds::addBumm(std::string s)
{
	bummBuffers.push_back(new sf::SoundBuffer());
	(*(bummBuffers.end()-1))->loadFromFile(s);
	bumms.push_back(new sf::Sound());
	(*(bumms.end()-1))->setBuffer(**(bummBuffers.end()-1)); 
	(*(bumms.end()-1))->setLoop(false);
	(*(bumms.end()-1))->setPitch(0.8f);
	(*(bumms.end()-1))->setVolume(75.f);
}
void Sounds::playBumm()
{
	bumms[stage]->play();
	if(++stage == bumms.size()) stage = 0;
}