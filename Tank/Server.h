#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <list>
#include <iostream>
#include "MessageObject.hpp"
#include "Client.h"
#include "ClientManager.h"

class Server
{
public:
	Server(unsigned int);
	~Server();
	MessageObject recieve(sf::TcpSocket&);

private:
	unsigned int port;
	sf::TcpListener listener;
	sf::TcpSocket client;
	sf::SocketSelector selector;
	bool isRunning;
	sf::Thread input;

	void waitForClients();
	std::list<sf::TcpSocket*> clients;
	std::list<ClientManager*> cms;
	void getInput();
	void shutDown();
	void send(std::string, sf::TcpSocket&);
	void send(unsigned short, std::string, sf::TcpSocket&);
	void send(MessageObject m, sf::TcpSocket&);
	void sendAll(MessageObject);
	void sendAllExceptSender(MessageObject, sf::TcpSocket&);
};

#endif //SERVER_H