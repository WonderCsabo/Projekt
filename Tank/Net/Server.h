#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <list>
#include <iostream>
#include <deque>
#include "MessageObject.h"
#include "Client.h"
#include "ClientManager.h"
#include "../Util/Convert.h"
#include "../Logic/Map.h"
#include "../Util/Utils.h"

class Server
{
public:
	Server(unsigned int);
	~Server();
	MessageObject recieve(sf::TcpSocket&);

private:
	unsigned int port;
	sf::TcpListener listener;
	sf::SocketSelector selector;
	bool isRunning;
	bool canConnect;
	std::list<ClientManager*> cms;
	Map* map;

	void initGameProtocol(sf::TcpSocket*);
	void updatePlayers();
	void connectNewClient(sf::TcpSocket*);
	void manageClientMessages();

	void waitForClients();
	void getInput();
	void shutDown();
	void launch();
	sf::Socket::Status send(std::string, sf::TcpSocket&);
	sf::Socket::Status send(unsigned short, std::string, sf::TcpSocket&);
	sf::Socket::Status send(MessageObject m, sf::TcpSocket&);
	void sendAll(MessageObject);
	void sendPacketAll(sf::Packet&);
	void sendAllExceptSender(MessageObject, sf::TcpSocket&);
	void sendCurrentClients(sf::TcpSocket&);
};