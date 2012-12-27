#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Client.h"

class ClientManager
{
public:
	ClientManager(sf::TcpSocket*, std::string);
	~ClientManager();

	sf::TcpSocket* getSocket();

private:
	unsigned int port;
	sf::IpAddress address;
	std::string nickname;
	sf::TcpSocket* client;
};