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
	START = 102, //start the game
	ALLCT = 102, //all client
	MVMNT = 200, //movement message
	CMD   = 300, //command message
	UPD   = 301, //update
	NOTIFY= 302, //notify self
	NEWPL = 304, //new player connects
	PLAYER= 305, //player object
	MAP   = 306, //map object
	ACTION= 400, //action message
	DISC  = 301, //disconnect
	ERR   = 500  //general error message
	};

	unsigned short type;
	std::string message;

	MessageObject();
	MessageObject::MessageObject(const MessageObject&);
	MessageObject(std::string);
	MessageObject(unsigned short, std::string);

	std::string toString();

	MessageObject& operator=(const MessageObject& rhs);
};

	std::ostream& operator<<(std::ostream&, const MessageObject&);

	sf::Packet& operator<<(sf::Packet&, const MessageObject&);

	sf::Packet& operator>>(sf::Packet&, MessageObject&);

	bool operator==(const MessageObject& lhs, const MessageObject& rhs);