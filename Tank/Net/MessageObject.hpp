#pragma once

#ifndef MESSAGEOBJECT_HPP
#define MESSAGEOBJECT_HPP

#include <SFML\Network.hpp>
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

	//deault constructor, general type, null message
	MessageObject() : type(100), message("null") {};
	//general message with the specified string
	MessageObject(std::string message_) : type(100), message(message_) {};
	//message with specified type and message string
	MessageObject(unsigned short type_, std::string message_) : type(type_), message(message_) {};

	std::string toString()
	{
		std::stringstream ss;
		ss << type << " " << message;
		std::string ret;
		std::getline(ss, ret);
		return ret;
	}

	//out operator for messageobject
	friend std::ostream& operator<<(std::ostream& os, const MessageObject& obj)
    {
		os << obj.type << ' ' << obj.message;
		return os;
	}

	//out operator for message obejct, it can be passed to a packet
	friend sf::Packet& operator <<(sf::Packet& packet, const MessageObject& m)
	{
		return packet << m.type << m.message;
	}

	//in operator for message object, it can be loaded from a packet
	friend sf::Packet& operator >>(sf::Packet& packet, MessageObject& m)
	{
		return packet >> m.type >> m.message;
	}
};

#endif //MESSAGEOBJECT_HPP