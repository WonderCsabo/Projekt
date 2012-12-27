#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>

struct MessageObject
{
	//enum for message types
	enum MESSAGES
	{
	GNRL  = 100, //general message
	CONN  = 101, //connect, should send nickname in this message
	MVMNT = 200, //movement message
	CMD   = 300, //command message
	DISC  = 301, //disconnect
	ERR   = 500  //general error message
	};

	unsigned short type;
	std::string message;

	MessageObject();
	MessageObject(std::string);
	MessageObject(unsigned short, std::string);

	std::string toString();
};

	std::ostream& operator<<(std::ostream&, const MessageObject&);

	sf::Packet& operator<<(sf::Packet&, const MessageObject&);

	sf::Packet& operator>>(sf::Packet&, MessageObject&);
