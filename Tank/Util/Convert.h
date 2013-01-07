#pragma once
#ifndef CONVERT_H
#define CONVERT_H

#include <sstream>
#include <SFML/Network.hpp>

template <class T>
sf::Packet putToPacket(T& t)
{
	sf::Packet p;
	std::stringstream ss;
	ss << t;
	p.append(ss.str().c_str(), ss.str().size());
	return p;
}

template <class T>
T* getFromPacket(sf::Packet& packet)
{
	std::stringstream ss;
	ss.write((char*)packet.getData(), packet.getDataSize());
	T* t = new T();
	ss >> *t;
	return t;
}

template <class T>
sf::Packet putPointerContainerToPacket(T& t)
{
	std::stringstream ss;
	serializePointerContainer(t.begin(), t.end(), ss);
	sf::Packet packet;
	packet.append(ss.str().c_str(), ss.str().size());
	return packet;
}

template<typename T, typename Container>
void getPointerContainerFromPacket(sf::Packet& packet, Container& cont)
{
	std::stringstream ss;
	ss.write((char*)packet.getData(), packet.getDataSize());
	deserializePointerContainer<T>(cont, ss);
}

template <class T>
std::stringstream putToStream(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss;
}

template <class T>
T getFromStream(std::stringstream& ss)
{
	T t;
	ss >> t;
	return t;
}

int strtoint(std::string s);

#endif //CONVERT_H